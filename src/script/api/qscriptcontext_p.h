/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtScript module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL-ONLY$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSCRIPTCONTEXT_P_H
#define QSCRIPTCONTEXT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QVarLengthArray>
#include <QtCore/QPair>
#include "qscriptcontext.h"
#include "qscriptshareddata_p.h"
#include "qscriptvalue_p.h"
#include "v8.h"

QT_BEGIN_NAMESPACE

class QScriptEnginePrivate;
class QScriptContext;

class QScriptContextPrivate : public QScriptContext
{
    Q_DECLARE_PUBLIC(QScriptContext);

protected:
    enum AllocationType {HeapAllocation, StackAllocation};
    inline QScriptContextPrivate(const AllocationType type, QScriptEnginePrivate *engine); // the global context (member of QScriptEnginePrivate)
    inline QScriptContextPrivate(const AllocationType type, QScriptEnginePrivate *engine, const v8::Arguments *args, v8::Local<v8::Value> callee = v8::Local<v8::Value>(), v8::Local<v8::Object> customThisObject = v8::Local<v8::Object>()); // native function context (on the stack)
    inline QScriptContextPrivate(const AllocationType type, QScriptEnginePrivate *engine, const v8::AccessorInfo *accessor); // native acessors (on the stack)
    inline QScriptContextPrivate(const AllocationType type, QScriptEnginePrivate *engine, v8::Handle<v8::Context> context); // from QScriptEngine::pushContext
    inline QScriptContextPrivate(const AllocationType type, QScriptContextPrivate *parent, v8::Handle<v8::StackFrame> frame); // internal, for js frame (allocated in parentContext())

public:
    class Stack;
    class Heap;
    template<class T>
    class Handle : protected v8::Handle<T>
    {
    public:
        typedef QScriptContextPrivate::AllocationType Type;

        Handle()
            : m_type(HeapAllocation) // lazy fall-back to Persistent
        {}

        Handle(Type type)
            : m_type(type)
        {}

        Handle(Type type, v8::Handle<T> handle)
            : m_type(type)
        {
            switch (m_type){
            case Local: *asLocal() = v8::Local<T>::New(handle); break;
            case Persistent: *asPersistent() = v8::Persistent<T>::New(handle); break;
            }
        }

        Handle(Type type, v8::Local<T> handle)
            : m_type(type)
        {
            switch (m_type){
            case Local:
                // We do not need to call Local::New because this local is already protected by
                // a higher HandleScope that would survive longer than this QScriptContextPrivate
                *asLocal() = handle;
                break;
            case Persistent: *asPersistent() = v8::Persistent<T>::New(handle); break;
            }
        }


        Handle(const Handle<T>& handle)
            : v8::Handle<T>(*handle)
            , m_type(handle.m_type)
        {
            switch (m_type){
            case Local:
                // The other handle is already protected, its live time would the same or a bit longer
                // so we do not need Local::New here.
                break;
            case Persistent: *asPersistent() = v8::Persistent<T>::New(handle); break;
            }
        }

        void operator =(v8::Handle<T> handle)
        {
            switch (m_type){
            case Local: *asLocal() = v8::Local<T>::New(handle); break;
            case Persistent:
                asPersistent()->Dispose();
                *asPersistent() = v8::Persistent<T>::New(handle);
                break;
            }
        }

        void operator =(v8::Local<T> handle)
        {
            switch (m_type){
            case Local:
                // The other handle is already protected, its live time would the same or a bit longer
                // so we do not need Local::New here.
                *asLocal() = handle;
                break;
            case Persistent:
                asPersistent()->Dispose();
                *asPersistent() = v8::Persistent<T>::New(handle);
                break;
            }
        }

        void operator =(Handle<T> handle)
        {
            Q_ASSERT(handle.m_type == m_type);
            switch (m_type) {
            case Local:
                // The other handle is already protected, its live time would the same or a bit longer
                // so we do not need Local::New here.
                *asLocal() = *handle.asLocal();
                break;
            case Persistent:
                asPersistent()->Dispose();
                *asPersistent() = v8::Persistent<T>::New(handle);
                break;
            }
        }

        void Dispose()
        {
            if (m_type == Persistent) {
                asPersistent()->Dispose();
                // FIXME: maybe it is not needed ?
                asPersistent()->Clear();
            }
        }

        inline T* operator->() const { return v8::Handle<T>::operator ->(); }
        inline T* operator*() const { return v8::Handle<T>::operator *(); }
        inline bool IsEmpty() const { return v8::Handle<T>::IsEmpty(); }
        inline v8::Handle<T> v8Handle() const { return v8::Handle<T>(*this); }

    private:
        static const int Persistent = QScriptContextPrivate::HeapAllocation;
        static const int Local = QScriptContextPrivate::StackAllocation;
        const Type m_type;

        inline v8::Persistent<T> *asPersistent()
        {
            Q_ASSERT(m_type == Persistent);
            return reinterpret_cast<v8::Persistent<T> *>(this);
        }

        inline v8::Local<T> *asLocal()
        {
            Q_ASSERT(m_type == Local);
            return reinterpret_cast<v8::Local<T> *>(this);
        }
    };


    static QScriptContextPrivate *get(const QScriptContext *q) { Q_ASSERT(q->d_ptr); return q->d_ptr; }
    static QScriptContext *get(QScriptContextPrivate *d) { return d->q_func(); }

    inline ~QScriptContextPrivate();

    inline bool isGlobalContext() const { return !parent; }
    inline bool isNativeFunction() const { return arguments; }
    inline bool isNativeAccessor() const { return accessorInfo; }
    inline bool isJSFrame() const { return !frame.IsEmpty(); }
    inline bool isPushedContext() const { return !context.IsEmpty() && !arguments && !accessorInfo; }

    inline QScriptPassPointer<QScriptValuePrivate> argument(int index) const;
    inline int argumentCount() const;
    inline QScriptPassPointer<QScriptValuePrivate> argumentsObject() const;
    v8::Handle<v8::Object> thisObject() const;
    inline void setThisObject(QScriptValuePrivate *);
    inline QScriptPassPointer<QScriptValuePrivate> callee() const;

    inline QScriptPassPointer<QScriptValuePrivate> activationObject() const;
    inline void setActivationObject(QScriptValuePrivate *);
    inline QScriptValueList scopeChain() const;
    inline void pushScope(QScriptValuePrivate *object);
    inline QScriptPassPointer<QScriptValuePrivate> popScope();
    inline QScriptPassPointer<QScriptValuePrivate> createArgumentsObject();
    inline void initializeArgumentsProperty();

    inline v8::Handle<v8::Value> throwError(Error error, const QString &text);

    const AllocationType m_allocation;
    QScriptContext* q_ptr;
    QScriptEnginePrivate *engine;
    const v8::Arguments *arguments;
    const v8::AccessorInfo *accessorInfo;
    Handle<v8::Context> context;
    QList<Handle<v8::Context> > scopes;
    Handle<v8::Context> inheritedScope;
    QScriptContextPrivate *parent; //the parent native frame as seen by the engine
    mutable QScriptContextPrivate *previous; //the previous js frame (lazily build)
    Handle<v8::StackFrame> frame; //only for js frames
    QScriptSharedDataPointer<QScriptValuePrivate> argsObject;
    Handle<v8::Object> m_thisObject;
    Handle<v8::Value> m_callee;
    bool hasArgumentGetter;

    static const int stackTraceLimit = 100;

private:
    static v8::Handle<v8::Value> argumentsPropertyGetter(v8::Local<v8::String> , const v8::AccessorInfo &);
    Q_DISABLE_COPY(QScriptContextPrivate)
};

/**
  \internal
  Optimised context that use Local handles instead of persistent
  \attention this class doesn't manage HandleScope it is left to user of this class
  */
class QScriptContextPrivate::Stack : public QScriptContextPrivate
{
public:
    inline Stack(QScriptEnginePrivate *engine); // the global context (member of QScriptEnginePrivate)
    inline Stack(QScriptEnginePrivate *engine, const v8::Arguments *args, v8::Local<v8::Value> callee = v8::Local<v8::Value>(), v8::Local<v8::Object> customThisObject = v8::Local<v8::Object>()); // native function context (on the stack)
    inline Stack(QScriptEnginePrivate *engine, const v8::AccessorInfo *accessor); // native acessors (on the stack)
    // Only base class is used so destructor here is pointless
private:
    // no heap allocation is allowed these operators are not defined
    inline void *operator new(size_t);
    inline void *operator new(size_t, void*);
};

/**
  \internal
  Context that use persistent handles, it would work on a heap as on a stack. It is a bit slower then Stack version
  */
class QScriptContextPrivate::Heap : public QScriptContextPrivate
{
public:
    inline Heap(QScriptEnginePrivate *engine); // the global context (member of QScriptEnginePrivate)
    inline Heap(QScriptEnginePrivate *engine, v8::Handle<v8::Context> context); // from QScriptEngine::pushContext
    inline Heap(QScriptContextPrivate *parent, v8::Handle<v8::StackFrame> frame); // internal, for js frame (allocated in parentContext())
    // Only base class is used so a destructor here is pointless
};

QT_END_NAMESPACE

#endif

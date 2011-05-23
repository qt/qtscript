TEMPLATE=subdirs
SUBDIRS=\
           qscriptable \
           qscriptclass \
           qscriptcontext \
           qscriptcontextinfo \
           qscriptengine \
           qscriptenginestable \
           qscriptengineagent \
           qscriptenginedebugger \
           qscriptextensionplugin \
           qscriptextqobject \
           qscriptjstestsuite \
           qscriptstring \
           qscriptv8testsuite \
           qscriptvalue \
           qscriptvaluegenerated \
           qscriptvaluestable \
           qscriptvalueiterator

!contains(QT_CONFIG,private-tests):SUBDIRS -= \
           qscriptcontext \

!cross_compile:                             SUBDIRS += host.pro


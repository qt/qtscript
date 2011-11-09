TEMPLATE=subdirs
SUBDIRS=\
           qscriptable \
           qscriptclass \
           qscriptcontext \
           qscriptcontextinfo \
           qscriptengine \
           qscriptengineagent \
           qscriptenginedebugger \
           qscriptextensionplugin \
           qscriptextqobject \
           qscriptjstestsuite \
           qscriptstring \
           qscriptv8testsuite \
           qscriptvalue \
           qscriptvaluegenerated \
           qscriptvalueiterator \
           qtipc \

!contains(QT_CONFIG, private_tests):SUBDIRS -= \
           qscriptcontext \
           qtipc \

!cross_compile:                             SUBDIRS += host.pro

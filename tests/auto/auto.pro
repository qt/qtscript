TEMPLATE=subdirs
SUBDIRS=\
           qscriptable \
           qscriptclass \
           qscriptcontext \
           qscriptcontextinfo \
           qscriptengine \
           qscriptenginedebugger \
           qscriptextensionplugin \
           qscriptextqobject \
           qscriptjstestsuite \
           qscriptstring \
           qscriptv8testsuite \
           qscriptvalue \
           qscriptvaluegenerated \
           qscriptvalueiterator \
           qscriptqwidgets \
           cmake \
#           qtipc \

!contains(QT_CONFIG, private_tests):SUBDIRS -= \
           qscriptcontext \
           qtipc \
           qscriptengineagent

!cross_compile:                             SUBDIRS += host.pro

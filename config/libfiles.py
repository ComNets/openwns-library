libname = 'wns'
srcFiles = [
    'src/Assure.cpp',
    'src/Exception.cpp',
    'src/TestFixture.cpp',
    'src/StopWatch.cpp',
    'src/Chamaeleon.cpp',
    'src/IOutputStreamable.cpp',
    'src/PythonicOutput.cpp',
    'src/Backtrace.cpp',
    'src/demangle.cpp',
    'src/Object.cpp',

    # module
    'src/module/Base.cpp',
    'src/module/Release.cpp',
    'src/module/DateTime.cpp',
    'src/simulator/IApplication.cpp',
    'src/simulator/Application.cpp',
    'src/simulator/SignalHandler.cpp',
    'src/simulator/SignalHandlerCallback.cpp',
    'src/simulator/AbortHandler.cpp',
    'src/simulator/SegmentationViolationHandler.cpp',
    'src/simulator/InterruptHandler.cpp',
    'src/simulator/CPUTimeExhaustedHandler.cpp',
    'src/simulator/ISimulator.cpp',
    'src/simulator/Simulator.cpp',
    'src/simulator/UnitTests.cpp',
    'src/simulator/ISimulationModel.cpp',
    'src/simulator/StatusReport.cpp',
    'src/simulator/ProbeWriter.cpp',
    'src/simulator/OutputPreparation.cpp',
    'src/pyconfig/Object.cpp',
    'src/pyconfig/View.cpp',
    'src/pyconfig/Parser.cpp',
    'src/pyconfig/Sequence.cpp',
    'src/pyconfig/helper/Functions.cpp',
    'src/events/scheduler/IEvent.cpp',
    'src/events/scheduler/Interface.cpp',
    'src/events/scheduler/CommandQueue.cpp',
    'src/events/scheduler/Map.cpp',
    'src/events/scheduler/INotification.cpp',
    'src/events/scheduler/Monitor.cpp',
    'src/events/scheduler/RealTime.cpp',
    'src/events/CanTimeout.cpp',
    'src/events/PeriodicTimeout.cpp',
    'src/events/PeriodicRealTimeout.cpp',

    'src/evaluation/statistics/stateval.cpp',
    'src/evaluation/statistics/moments.cpp',
    'src/evaluation/statistics/pdf.cpp',

    'src/logger/Master.cpp',
    'src/logger/Message.cpp',
    'src/logger/Logger.cpp',
    'src/logger/OutputStrategy.cpp',
    'src/logger/CoutOutput.cpp',
    'src/logger/CerrOutput.cpp',
    'src/logger/FileOutput.cpp',
    'src/logger/ConsoleFormat.cpp',
    'src/logger/XMLFormat.cpp',
    'src/logger/DelimiterFormat.cpp',
    'src/logger/SQLiteFormat.cpp',
    'src/logger/FormatStrategy.cpp',
    'src/probe/bus/Context.cpp',
    'src/probe/bus/ContextFilterProbeBus.cpp',
    'src/probe/bus/ContextProvider.cpp',
    'src/probe/bus/ContextCollector.cpp',
    'src/probe/bus/LoggingProbeBus.cpp',
    'src/probe/bus/TimeSeriesProbeBus.cpp',
    'src/probe/bus/PassThroughProbeBus.cpp',
    'src/probe/bus/ProbeBus.cpp',
    'src/probe/bus/ProbeBusRegistry.cpp',
    'src/probe/bus/PythonProbeBus.cpp',
    'src/probe/bus/SettlingTimeGuardProbeBus.cpp',
    'src/probe/bus/StatEvalProbeBus.cpp',
    'src/probe/bus/TableProbeBus.cpp',
    'src/probe/bus/TextProbeBus.cpp',
    'src/probe/bus/TimeWindowProbeBus.cpp',

    'src/probe/bus/detail/ObserverPimpl.cpp',
    'src/probe/bus/detail/OutputFormatter.cpp',
    'src/probe/bus/detail/SubjectPimpl.cpp',
    'src/probe/bus/detail/Sorter.cpp',
    'src/probe/bus/detail/StatEvalTable.cpp',

    'src/testing/DetailedListener.cpp',
    'src/testing/TestTool.cpp',
    
    'src/osi/PDU.cpp',
    'src/osi/PCI.cpp',

    'src/node/Node.cpp',
    'src/node/NodeSimulationModel.cpp',
    'src/node/component/Component.cpp',
    'src/node/component/FQSN.cpp',

    'src/service/tl/PortPool.cpp',

    'src/distribution/Fixed.cpp',
    'src/distribution/NegExp.cpp',
    'src/distribution/Norm.cpp',
    'src/distribution/Uniform.cpp',
    'src/distribution/DiscreteUniform.cpp',
    'src/distribution/Pareto.cpp',
    'src/distribution/Binomial.cpp',
    'src/distribution/Geometric.cpp',
    'src/distribution/Erlang.cpp',
    'src/distribution/Poisson.cpp',
    'src/distribution/CDFTable.cpp',
    'src/distribution/TimeDependent.cpp',
    'src/distribution/Operation.cpp',
    'src/distribution/Rice.cpp',

    'src/queuingsystem/Job.cpp',
    'src/queuingsystem/JobContextProvider.cpp',
    'src/queuingsystem/MM1Step1.cpp',
    'src/queuingsystem/MM1Step2.cpp',
    'src/queuingsystem/MM1Step3.cpp',
    'src/queuingsystem/MM1Step5.cpp',
    'src/queuingsystem/MM1Step6.cpp',

    'src/tests/AverageTest.cpp',
    'src/tests/AssureTest.cpp',
    'src/tests/ChamaeleonTest.cpp',
    'src/tests/ExceptionTest.cpp',
    'src/tests/TypeInfoTest.cpp',
    'src/tests/FunctorTest.cpp',
    'src/tests/StaticFactoryTest.cpp',
    'src/tests/SmartPtrTest.cpp',
    'src/tests/SmartPtrWithDebuggingTest.cpp',
    'src/tests/PythonicOutputTest.cpp',
    'src/tests/StopWatchTest.cpp',
    'src/tests/BacktraceTest.cpp',
    'src/tests/ObserverTest.cpp',
    'src/tests/ObjectTest.cpp',
    'src/tests/IntervalTest.cpp',
    'src/tests/EnumeratorTest.cpp',

    'src/module/tests/ModuleTest.cpp',
    'src/module/tests/MultiTypeFactoryTest.cpp',
    'src/simulator/tests/MainTest.cpp',
    'src/container/tests/FastListTest.cpp',
    'src/container/tests/UntypedRegistryTest.cpp',
    'src/container/tests/RegistryTest.cpp',
    'src/container/tests/DynamicMatrixTest.cpp',
    'src/container/tests/PoolTest.cpp',
    'src/container/tests/RangeMapTest.cpp',

    'src/pyconfig/tests/ParserTest.cpp',
    'src/pyconfig/tests/ViewTest.cpp',
    'src/pyconfig/tests/SequenceTest.cpp',
    'src/pyconfig/helper/tests/FunctionsTest.cpp',
    'src/logger/tests/MasterTest.cpp',
    'src/logger/tests/MessageTest.cpp',
    'src/logger/tests/LoggerTest.cpp',
    'src/logger/tests/LoggerTestHelper.cpp',
    'src/probe/bus/tests/ContextTest.cpp',
    'src/probe/bus/tests/ContextFilterProbeBusTest.cpp',
    'src/probe/bus/tests/ContextProviderTest.cpp',
    'src/probe/bus/tests/ContextProviderCollectionTest.cpp',
    'src/probe/bus/tests/ContextCollectorTest.cpp',
    'src/probe/bus/tests/PassThroughProbeBusTest.cpp',
    'src/probe/bus/tests/ProbeBusRegistryTest.cpp',
    'src/probe/bus/tests/ProbeBusStub.cpp',
    'src/probe/bus/tests/PythonProbeBusTest.cpp',
    'src/probe/bus/tests/TimeWindowProbeBusTest.cpp',
    'src/probe/bus/tests/TableProbeBusTest.cpp',
    'src/probe/bus/tests/DevelopersGuideTest.cpp',
    'src/probe/bus/tests/DevelopersGuideTestCollector.cpp',
    'src/probe/bus/detail/tests/SorterTest.cpp',

    'src/evaluation/statistics/tests/StatEvalTest.cpp',

    'src/events/tests/MemberFunctionTest.cpp',
    'src/events/tests/DelayedMemberFunctionTest.cpp',
    'src/events/scheduler/tests/CallableTest.cpp',
    'src/events/scheduler/tests/InterfaceTest.cpp',
    'src/events/scheduler/tests/MapInterfaceTest.cpp',
    'src/events/scheduler/tests/PerformanceTest.cpp',
    'src/events/scheduler/tests/MapPerformanceTest.cpp',
    'src/events/scheduler/tests/BestPracticesTest.cpp',
    'src/events/scheduler/tests/RealTimeTest.cpp',
    'src/events/tests/CanTimeoutTest.cpp',
    'src/events/tests/PeriodicTimeoutTest.cpp',
    'src/events/tests/PeriodicRealTimeoutTest.cpp',

    'src/osi/tests/PCITest.cpp',
    'src/osi/tests/PDUTest.cpp',

    'src/service/nl/tests/Address.cpp',

    'src/node/tests/NodeTest.cpp',
    'src/node/tests/NodeHeaderReaderTest.cpp',
    'src/node/tests/Stub.cpp',   
    'src/node/component/tests/ComponentStub.cpp',
    'src/node/component/tests/ComponentTest.cpp',
    'src/node/component/tests/IP.cpp',
    'src/node/component/tests/TCP.cpp',
    'src/node/component/tests/FQSNTest.cpp',

    'src/service/tl/tests/PortPoolTest.cpp',

    'src/distribution/tests/FixedTest.cpp',
    'src/distribution/tests/VarEstimator.cpp',
    'src/distribution/tests/NegExpTest.cpp',
    'src/distribution/tests/ErlangTest.cpp',
    'src/distribution/tests/NormTest.cpp',
    'src/distribution/tests/UniformTest.cpp',
    'src/distribution/tests/DiscreteUniformTest.cpp',
    'src/distribution/tests/PoissonTest.cpp',
    'src/distribution/tests/GeometricTest.cpp',
    'src/distribution/tests/ParetoTest.cpp',
    'src/distribution/tests/BinomialTest.cpp',
    'src/distribution/tests/CDFTableTest.cpp',
    'src/distribution/tests/RiceTest.cpp',
    'src/distribution/tests/TimeDependentTest.cpp',
    'src/distribution/tests/OperationTest.cpp',
]

hppFiles = [
'src/Average.hpp',
'src/Enumerator.hpp',
'src/Interval.hpp',
'src/Object.hpp',
'src/Ttos.hpp',
'src/Types.hpp',
'src/container/BinaryTree.hpp',
'src/container/Pool.hpp',
'src/container/RangeMap.hpp',
'src/container/Tree.hpp',
'src/distribution/Binomial.hpp',
'src/distribution/CDFTable.hpp',
'src/distribution/DiscreteUniform.hpp',
'src/distribution/Distribution.hpp',
'src/distribution/Erlang.hpp',
'src/distribution/Fixed.hpp',
'src/distribution/ForwardRecurrenceTime.hpp',
'src/distribution/Geometric.hpp',
'src/distribution/NegExp.hpp',
'src/distribution/Norm.hpp',
'src/distribution/Operation.hpp',
'src/distribution/Pareto.hpp',
'src/distribution/Poisson.hpp',
'src/distribution/RNGConfigCreator.hpp',
'src/distribution/Rice.hpp',
'src/distribution/TimeDependent.hpp',
'src/distribution/Uniform.hpp',
'src/distribution/tests/CDFTableTest.hpp',
'src/distribution/tests/DiscreteUniformTest.hpp',
'src/distribution/tests/ErlangTest.hpp',
'src/distribution/tests/FixedTest.hpp',
'src/distribution/tests/GeometricTest.hpp',
'src/distribution/tests/NegExpTest.hpp',
'src/distribution/tests/NormTest.hpp',
'src/distribution/tests/OperationTest.hpp',
'src/distribution/tests/ParetoTest.hpp',
'src/distribution/tests/PoissonTest.hpp',
'src/distribution/tests/RiceTest.hpp',
'src/distribution/tests/UniformTest.hpp',
'src/distribution/tests/VarEstimator.hpp',
'src/queuingsystem/Job.hpp',
'src/queuingsystem/JobContextProvider.hpp',
'src/queuingsystem/MM1Step1.hpp',
'src/queuingsystem/MM1Step6.hpp',
'src/queuingsystem/MM1Step3.hpp',
'src/queuingsystem/MM1Step5.hpp',
'src/queuingsystem/MM1Step2.hpp',
'src/Assure.hpp',
'src/LongCreator.hpp',
'src/rng/RNGen.hpp',
'src/Singleton.hpp',
'src/RefCountable.hpp',
'src/Chamaeleon.hpp',
'src/logger/CoutOutput.hpp',
'src/logger/FormatStrategy.hpp',
'src/logger/SQLiteFormat.hpp',
'src/logger/OutputStrategy.hpp',
'src/logger/Master.hpp',
'src/logger/tests/LoggerTest.hpp',
'src/logger/tests/MasterTest.hpp',
'src/logger/tests/LoggerTestHelper.hpp',
'src/logger/tests/MessageTest.hpp',
'src/logger/FileOutput.hpp',
'src/logger/ConsoleFormat.hpp',
'src/logger/CerrOutput.hpp',
'src/logger/XMLFormat.hpp',
'src/logger/Message.hpp',
'src/logger/DelimiterFormat.hpp',
'src/logger/Logger.hpp',
'src/NonCopyable.hpp',
'src/SubjectInterface.hpp',
'src/SmartPtr.hpp',
'src/evaluation/statistics/stateval.hpp',
'src/evaluation/statistics/moments.hpp',
'src/evaluation/statistics/pdf.hpp',
'src/events/CanTimeout.hpp',
'src/events/NoOp.hpp',
'src/events/MemberFunction.hpp',
'src/events/PeriodicRealTimeout.hpp',
'src/events/PeriodicTimeout.hpp',
'src/events/scheduler/CommandQueue.hpp',
'src/events/scheduler/Map.hpp',
'src/events/scheduler/Callable.hpp',
'src/events/scheduler/ICommand.hpp',
'src/events/scheduler/tests/InterfaceTest.hpp',
'src/events/scheduler/tests/PerformanceTest.hpp',
'src/events/scheduler/RealTime.hpp',
'src/events/scheduler/NullCommand.hpp',
'src/events/scheduler/Monitor.hpp',
'src/events/scheduler/INotification.hpp',
'src/events/scheduler/IEvent.hpp',
'src/events/scheduler/Interface.hpp',
'src/events/tests/PeriodicTimeoutTest.hpp',
'src/SmartPtrBase.hpp',
'src/Python.hpp',
'src/Subject.hpp',
'src/Functor.hpp',
'src/IOutputStreamable.hpp',
'src/PyConfigViewCreator.hpp',
'src/module/Module.hpp',
'src/module/tests/ModuleTest.hpp',
'src/module/tests/MultiTypeFactoryTest.hpp',
'src/module/CurrentVersion.hpp',
'src/module/DateTime.hpp',
'src/module/DependencyList.hpp',
'src/module/Version.hpp',
'src/module/VersionInformation.hpp',
'src/module/Release.hpp',
'src/module/MultiTypeFactory.hpp',
'src/module/Base.hpp',
'src/node/Interface.hpp',
'src/node/Node.hpp',
'src/node/NodeSimulationModel.hpp',
'src/node/Registry.hpp',
'src/node/component/Component.hpp',
'src/node/component/ConfigCreator.hpp',
'src/node/component/FQSN.hpp',
'src/node/component/Interface.hpp',
'src/node/component/tests/ComponentStub.hpp',
'src/node/component/tests/ComponentTest.hpp',
'src/node/component/tests/FQSNTest.hpp',
'src/node/component/tests/IP.hpp',
'src/node/component/tests/TCP.hpp',
'src/node/tests/NodeTest.hpp',
'src/node/tests/Stub.hpp',
'src/osi/PCI.hpp',
'src/osi/PDU.hpp',
'src/probe/bus/ContextCollector.hpp',
'src/probe/bus/ContextProvider.hpp',
'src/probe/bus/ContextProviderCollection.hpp',
'src/service/Service.hpp',
'src/service/nl/Address.hpp',
'src/service/nl/tests/Address.hpp',
'src/service/tl/Connection.hpp',
'src/service/tl/ConnectionHandler.hpp',
'src/service/tl/DataHandler.hpp',
'src/service/tl/FlowID.hpp',
'src/service/tl/PortPool.hpp',
'src/service/tl/Service.hpp',
'src/Backtrace.hpp',
'src/simulator/Bit.hpp',
'src/simulator/Main.hpp',
'src/simulator/InterruptHandler.hpp',
'src/simulator/CPUTimeExhaustedHandler.hpp',
'src/simulator/ISimulator.hpp',
'src/simulator/IApplication.hpp',
'src/simulator/UnitTests.hpp',
'src/simulator/ISimulationModel.hpp',
'src/simulator/Time.hpp',
'src/simulator/SignalHandlerCallback.hpp',
'src/simulator/OutputPreparation.hpp',
'src/simulator/ProbeWriter.hpp',
'src/simulator/StatusReport.hpp',
'src/simulator/AbortHandler.hpp',
'src/simulator/Application.hpp',
'src/simulator/SignalHandler.hpp',
'src/simulator/SegmentationViolationHandler.hpp',
'src/simulator/Simulator.hpp',
'src/Exception.hpp',
'src/probe/bus/ContextFilterProbeBus.hpp',
'src/probe/bus/PassThroughProbeBus.hpp',
'src/probe/bus/PythonProbeBus.hpp',
'src/probe/bus/TableProbeBus.hpp',
'src/probe/bus/TextProbeBus.hpp',
'src/probe/bus/TimeSeriesProbeBus.hpp',
'src/probe/bus/tests/ProbeBusStub.hpp',
'src/probe/bus/SettlingTimeGuardProbeBus.hpp',
'src/probe/bus/LoggingProbeBus.hpp',
'src/probe/bus/ProbeBus.hpp',
'src/probe/bus/ProbeBusRegistry.hpp',
'src/probe/bus/Context.hpp',
'src/probe/bus/TimeWindowProbeBus.hpp',
'src/probe/bus/StatEvalProbeBus.hpp',
'src/probe/bus/detail/IProbeBusNotification.hpp',
'src/probe/bus/detail/MeasurementFunctor.hpp',
'src/probe/bus/detail/ObserverPimpl.hpp',
'src/probe/bus/detail/OutputFormatter.hpp',
'src/probe/bus/detail/SubjectPimpl.hpp',
'src/probe/bus/detail/Sorter.hpp',
'src/probe/bus/detail/StatEvalTable.hpp',
'src/PythonicOutput.hpp',
'src/pyconfig/helper/tests/FunctionsTest.hpp',
'src/pyconfig/helper/Functions.hpp',
'src/pyconfig/Parser.hpp',
'src/pyconfig/Converter.hpp',
'src/pyconfig/tests/SequenceTest.hpp',
'src/pyconfig/tests/ViewTest.hpp',
'src/pyconfig/tests/ParserTest.hpp',
'src/pyconfig/View.hpp',
'src/pyconfig/Sequence.hpp',
'src/pyconfig/Object.hpp',
'src/testing/DetailedListener.hpp',
'src/testing/TestTool.hpp',
'src/ObserverInterface.hpp',
'src/TypeInfo.hpp',
'src/StaticFactory.hpp',
'src/container/DynamicMatrix.hpp',
'src/container/FastListEnabler.hpp',
'src/container/Registry.hpp',
'src/container/FastListNode.hpp',
'src/container/FastList.hpp',
'src/container/UntypedRegistry.hpp',
'src/Conversion.hpp',
'src/TestFixture.hpp',
'src/demangle.hpp',
'src/StopWatch.hpp',
'src/Observer.hpp',
'src/tests/AverageTest.hpp',
'src/tests/EnumeratorTest.hpp',
'src/tests/IntervalTest.hpp',
]

pyconfig = [
'openwns/distribution.py',
'openwns/node.py',
'openwns/simulator.py',
'openwns/queuingsystem.py',
'openwns/eventscheduler.py',
'openwns/rng.py',
'openwns/tests/simulatorTest.py',
'openwns/tests/__init__.py',
'openwns/tests/nodeTest.py',
'openwns/module.py',
'openwns/logger.py',
'openwns/probebus.py',
'openwns/interface.py',
'openwns/pyconfig.py',
'openwns/__init__.py',
'openwns/backend/pyconfig.py',
'openwns/backend/__init__.py',
'openwns/evaluation/__init__.py',
'openwns/evaluation/formatters.py',
'openwns/evaluation/generators.py',
'openwns/evaluation/statistics.py',
'openwns/evaluation/tree.py',
'openwns/evaluation/wrappers.py',
'openwns/evaluation/default.py',
'openwns/geometry/position.py',
'openwns/geometry/__init__.py',
]
libraries = []
Return('libname srcFiles hppFiles pyconfig libraries')

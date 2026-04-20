<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio FileVersion="4.9"?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1" />
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4">
    <Task Name="SPL_CalcTe" Source="UnitTestSample.Samples.Tests_Program.Tests_MyCalcLib_C.SPL_CalcTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SPL_CalcT1" Source="UnitTestSample.Samples.Tests_Program.Tests_MyCalcLib_C.SPL_CalcTest_Variants.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="Tests_Padd" Source="UnitTests.UnitTests.Tests_PaddleMotor_C.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#5" />
  <TaskClass Name="Cyclic#6" />
  <TaskClass Name="Cyclic#7" />
  <TaskClass Name="Cyclic#8" />
  <Binaries>
    <BinaryObject Name="mvLoader" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="udbdef" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TCData" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="iomap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="asfw" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="arconfig" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="ashwd" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="sysconf" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="ashwac" Source="" Memory="UserROM" Language="Binary" />
  </Binaries>
  <Libraries>
    <LibraryObject Name="Runtime" Source="Libraries.Runtime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries.sys_lib.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsIecCon" Source="Libraries.AsIecCon.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="astime" Source="Libraries.astime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsARCfg" Source="Libraries.AsARCfg.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries.AsBrStr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="UnitTest" Source="Libraries.UnitTest.UnitTest.lby" Memory="None" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="UtWs" Source="Libraries.UnitTest.UtWs.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="UtMgr" Source="Libraries.UnitTest.UtMgr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="SPLMyCalc" Source="UnitTestSample.Samples.Tests_Program.SPLMyCalc.lby" Memory="UserROM" Language="IEC" Debugging="true" />
    <LibraryObject Name="Library" Source="Libraries.Library.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="arssl" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="fileio" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
  </Libraries>
</SwConfiguration>
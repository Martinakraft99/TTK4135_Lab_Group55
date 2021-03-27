  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 7;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helicopterD4_P)
    ;%
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% helicopterD4_P.K
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_P.K_ed
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 12;
	
	  ;% helicopterD4_P.K_ei
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 13;
	
	  ;% helicopterD4_P.K_ep
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 14;
	
	  ;% helicopterD4_P.K_pd
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 15;
	
	  ;% helicopterD4_P.K_pp
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 16;
	
	  ;% helicopterD4_P.Vd_ff
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 17;
	
	  ;% helicopterD4_P.Vs_ff
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 18;
	
	  ;% helicopterD4_P.elevation_gain
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 19;
	
	  ;% helicopterD4_P.travel_gain
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILWriteAnalog_channels
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 48;
      section.data(48)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILInitialize_OOTerminate
	  section.data(1).logicalSrcIdx = 11;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_P.HILInitialize_OOExit
	  section.data(2).logicalSrcIdx = 12;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helicopterD4_P.HILInitialize_OOStart
	  section.data(3).logicalSrcIdx = 13;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helicopterD4_P.HILInitialize_OOEnter
	  section.data(4).logicalSrcIdx = 14;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helicopterD4_P.HILInitialize_AOFinal
	  section.data(5).logicalSrcIdx = 15;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helicopterD4_P.HILInitialize_POFinal
	  section.data(6).logicalSrcIdx = 16;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helicopterD4_P.HILInitialize_AIHigh
	  section.data(7).logicalSrcIdx = 17;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helicopterD4_P.HILInitialize_AILow
	  section.data(8).logicalSrcIdx = 18;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helicopterD4_P.HILInitialize_AOHigh
	  section.data(9).logicalSrcIdx = 19;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helicopterD4_P.HILInitialize_AOLow
	  section.data(10).logicalSrcIdx = 20;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helicopterD4_P.HILInitialize_AOInitial
	  section.data(11).logicalSrcIdx = 21;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helicopterD4_P.HILInitialize_AOWatchdog
	  section.data(12).logicalSrcIdx = 22;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helicopterD4_P.HILInitialize_POFrequency
	  section.data(13).logicalSrcIdx = 23;
	  section.data(13).dtTransOffset = 12;
	
	  ;% helicopterD4_P.HILInitialize_POLeading
	  section.data(14).logicalSrcIdx = 24;
	  section.data(14).dtTransOffset = 13;
	
	  ;% helicopterD4_P.HILInitialize_POTrailing
	  section.data(15).logicalSrcIdx = 25;
	  section.data(15).dtTransOffset = 14;
	
	  ;% helicopterD4_P.HILInitialize_POInitial
	  section.data(16).logicalSrcIdx = 26;
	  section.data(16).dtTransOffset = 15;
	
	  ;% helicopterD4_P.HILInitialize_POWatchdog
	  section.data(17).logicalSrcIdx = 27;
	  section.data(17).dtTransOffset = 16;
	
	  ;% helicopterD4_P.Pi_Value
	  section.data(18).logicalSrcIdx = 28;
	  section.data(18).dtTransOffset = 17;
	
	  ;% helicopterD4_P.TravelCounttorad_Gain
	  section.data(19).logicalSrcIdx = 29;
	  section.data(19).dtTransOffset = 18;
	
	  ;% helicopterD4_P.Gain_Gain
	  section.data(20).logicalSrcIdx = 30;
	  section.data(20).dtTransOffset = 19;
	
	  ;% helicopterD4_P.TravelTransferFcn_A
	  section.data(21).logicalSrcIdx = 31;
	  section.data(21).dtTransOffset = 20;
	
	  ;% helicopterD4_P.TravelTransferFcn_C
	  section.data(22).logicalSrcIdx = 32;
	  section.data(22).dtTransOffset = 21;
	
	  ;% helicopterD4_P.TravelTransferFcn_D
	  section.data(23).logicalSrcIdx = 33;
	  section.data(23).dtTransOffset = 22;
	
	  ;% helicopterD4_P.Gain_Gain_l
	  section.data(24).logicalSrcIdx = 34;
	  section.data(24).dtTransOffset = 23;
	
	  ;% helicopterD4_P.PitchCounttorad_Gain
	  section.data(25).logicalSrcIdx = 35;
	  section.data(25).dtTransOffset = 24;
	
	  ;% helicopterD4_P.Gain_Gain_a
	  section.data(26).logicalSrcIdx = 36;
	  section.data(26).dtTransOffset = 25;
	
	  ;% helicopterD4_P.PitchTransferFcn_A
	  section.data(27).logicalSrcIdx = 37;
	  section.data(27).dtTransOffset = 26;
	
	  ;% helicopterD4_P.PitchTransferFcn_C
	  section.data(28).logicalSrcIdx = 38;
	  section.data(28).dtTransOffset = 27;
	
	  ;% helicopterD4_P.PitchTransferFcn_D
	  section.data(29).logicalSrcIdx = 39;
	  section.data(29).dtTransOffset = 28;
	
	  ;% helicopterD4_P.Gain_Gain_ae
	  section.data(30).logicalSrcIdx = 40;
	  section.data(30).dtTransOffset = 29;
	
	  ;% helicopterD4_P.ElevationCounttorad_Gain
	  section.data(31).logicalSrcIdx = 41;
	  section.data(31).dtTransOffset = 30;
	
	  ;% helicopterD4_P.Gain_Gain_lv
	  section.data(32).logicalSrcIdx = 42;
	  section.data(32).dtTransOffset = 31;
	
	  ;% helicopterD4_P.elavation_offsetdeg_Value
	  section.data(33).logicalSrcIdx = 43;
	  section.data(33).dtTransOffset = 32;
	
	  ;% helicopterD4_P.ElevationTransferFcn_A
	  section.data(34).logicalSrcIdx = 44;
	  section.data(34).dtTransOffset = 33;
	
	  ;% helicopterD4_P.ElevationTransferFcn_C
	  section.data(35).logicalSrcIdx = 45;
	  section.data(35).dtTransOffset = 34;
	
	  ;% helicopterD4_P.ElevationTransferFcn_D
	  section.data(36).logicalSrcIdx = 46;
	  section.data(36).dtTransOffset = 35;
	
	  ;% helicopterD4_P.Gain_Gain_n
	  section.data(37).logicalSrcIdx = 47;
	  section.data(37).dtTransOffset = 36;
	
	  ;% helicopterD4_P.Gain1_Gain
	  section.data(38).logicalSrcIdx = 48;
	  section.data(38).dtTransOffset = 37;
	
	  ;% helicopterD4_P.Integrator_IC
	  section.data(39).logicalSrcIdx = 49;
	  section.data(39).dtTransOffset = 38;
	
	  ;% helicopterD4_P.Integrator_UpperSat
	  section.data(40).logicalSrcIdx = 50;
	  section.data(40).dtTransOffset = 39;
	
	  ;% helicopterD4_P.Integrator_LowerSat
	  section.data(41).logicalSrcIdx = 51;
	  section.data(41).dtTransOffset = 40;
	
	  ;% helicopterD4_P.Backgain_Gain
	  section.data(42).logicalSrcIdx = 52;
	  section.data(42).dtTransOffset = 41;
	
	  ;% helicopterD4_P.Frontgain_Gain
	  section.data(43).logicalSrcIdx = 53;
	  section.data(43).dtTransOffset = 42;
	
	  ;% helicopterD4_P.Gain_Gain_a1
	  section.data(44).logicalSrcIdx = 54;
	  section.data(44).dtTransOffset = 43;
	
	  ;% helicopterD4_P.BackmotorSaturation_UpperSat
	  section.data(45).logicalSrcIdx = 55;
	  section.data(45).dtTransOffset = 44;
	
	  ;% helicopterD4_P.BackmotorSaturation_LowerSat
	  section.data(46).logicalSrcIdx = 56;
	  section.data(46).dtTransOffset = 45;
	
	  ;% helicopterD4_P.FrontmotorSaturation_UpperSat
	  section.data(47).logicalSrcIdx = 57;
	  section.data(47).dtTransOffset = 46;
	
	  ;% helicopterD4_P.FrontmotorSaturation_LowerSat
	  section.data(48).logicalSrcIdx = 58;
	  section.data(48).dtTransOffset = 47;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 60;
	  section.data(2).dtTransOffset = 3;
	
	  ;% helicopterD4_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 61;
	  section.data(3).dtTransOffset = 4;
	
	  ;% helicopterD4_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 62;
	  section.data(4).dtTransOffset = 5;
	
	  ;% helicopterD4_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 63;
	  section.data(5).dtTransOffset = 6;
	
	  ;% helicopterD4_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 64;
	  section.data(6).dtTransOffset = 7;
	
	  ;% helicopterD4_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 65;
	  section.data(7).dtTransOffset = 8;
	
	  ;% helicopterD4_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 66;
	  section.data(8).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 68;
	  section.data(2).dtTransOffset = 8;
	
	  ;% helicopterD4_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 69;
	  section.data(3).dtTransOffset = 16;
	
	  ;% helicopterD4_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 70;
	  section.data(4).dtTransOffset = 24;
	
	  ;% helicopterD4_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 71;
	  section.data(5).dtTransOffset = 25;
	
	  ;% helicopterD4_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 72;
	  section.data(6).dtTransOffset = 33;
	
	  ;% helicopterD4_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 73;
	  section.data(7).dtTransOffset = 36;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 37;
      section.data(37)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 74;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_P.HILInitialize_AOTerminate
	  section.data(2).logicalSrcIdx = 75;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helicopterD4_P.HILInitialize_AOExit
	  section.data(3).logicalSrcIdx = 76;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helicopterD4_P.HILInitialize_DOTerminate
	  section.data(4).logicalSrcIdx = 77;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helicopterD4_P.HILInitialize_DOExit
	  section.data(5).logicalSrcIdx = 78;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helicopterD4_P.HILInitialize_POTerminate
	  section.data(6).logicalSrcIdx = 79;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helicopterD4_P.HILInitialize_POExit
	  section.data(7).logicalSrcIdx = 80;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helicopterD4_P.HILInitialize_CKPStart
	  section.data(8).logicalSrcIdx = 81;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helicopterD4_P.HILInitialize_CKPEnter
	  section.data(9).logicalSrcIdx = 82;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helicopterD4_P.HILInitialize_CKStart
	  section.data(10).logicalSrcIdx = 83;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helicopterD4_P.HILInitialize_CKEnter
	  section.data(11).logicalSrcIdx = 84;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helicopterD4_P.HILInitialize_AIPStart
	  section.data(12).logicalSrcIdx = 85;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helicopterD4_P.HILInitialize_AIPEnter
	  section.data(13).logicalSrcIdx = 86;
	  section.data(13).dtTransOffset = 12;
	
	  ;% helicopterD4_P.HILInitialize_AOPStart
	  section.data(14).logicalSrcIdx = 87;
	  section.data(14).dtTransOffset = 13;
	
	  ;% helicopterD4_P.HILInitialize_AOPEnter
	  section.data(15).logicalSrcIdx = 88;
	  section.data(15).dtTransOffset = 14;
	
	  ;% helicopterD4_P.HILInitialize_AOStart
	  section.data(16).logicalSrcIdx = 89;
	  section.data(16).dtTransOffset = 15;
	
	  ;% helicopterD4_P.HILInitialize_AOEnter
	  section.data(17).logicalSrcIdx = 90;
	  section.data(17).dtTransOffset = 16;
	
	  ;% helicopterD4_P.HILInitialize_AOReset
	  section.data(18).logicalSrcIdx = 91;
	  section.data(18).dtTransOffset = 17;
	
	  ;% helicopterD4_P.HILInitialize_DOPStart
	  section.data(19).logicalSrcIdx = 92;
	  section.data(19).dtTransOffset = 18;
	
	  ;% helicopterD4_P.HILInitialize_DOPEnter
	  section.data(20).logicalSrcIdx = 93;
	  section.data(20).dtTransOffset = 19;
	
	  ;% helicopterD4_P.HILInitialize_DOStart
	  section.data(21).logicalSrcIdx = 94;
	  section.data(21).dtTransOffset = 20;
	
	  ;% helicopterD4_P.HILInitialize_DOEnter
	  section.data(22).logicalSrcIdx = 95;
	  section.data(22).dtTransOffset = 21;
	
	  ;% helicopterD4_P.HILInitialize_DOReset
	  section.data(23).logicalSrcIdx = 96;
	  section.data(23).dtTransOffset = 22;
	
	  ;% helicopterD4_P.HILInitialize_EIPStart
	  section.data(24).logicalSrcIdx = 97;
	  section.data(24).dtTransOffset = 23;
	
	  ;% helicopterD4_P.HILInitialize_EIPEnter
	  section.data(25).logicalSrcIdx = 98;
	  section.data(25).dtTransOffset = 24;
	
	  ;% helicopterD4_P.HILInitialize_EIStart
	  section.data(26).logicalSrcIdx = 99;
	  section.data(26).dtTransOffset = 25;
	
	  ;% helicopterD4_P.HILInitialize_EIEnter
	  section.data(27).logicalSrcIdx = 100;
	  section.data(27).dtTransOffset = 26;
	
	  ;% helicopterD4_P.HILInitialize_POPStart
	  section.data(28).logicalSrcIdx = 101;
	  section.data(28).dtTransOffset = 27;
	
	  ;% helicopterD4_P.HILInitialize_POPEnter
	  section.data(29).logicalSrcIdx = 102;
	  section.data(29).dtTransOffset = 28;
	
	  ;% helicopterD4_P.HILInitialize_POStart
	  section.data(30).logicalSrcIdx = 103;
	  section.data(30).dtTransOffset = 29;
	
	  ;% helicopterD4_P.HILInitialize_POEnter
	  section.data(31).logicalSrcIdx = 104;
	  section.data(31).dtTransOffset = 30;
	
	  ;% helicopterD4_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 105;
	  section.data(32).dtTransOffset = 31;
	
	  ;% helicopterD4_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 106;
	  section.data(33).dtTransOffset = 32;
	
	  ;% helicopterD4_P.HILInitialize_DOFinal
	  section.data(34).logicalSrcIdx = 107;
	  section.data(34).dtTransOffset = 33;
	
	  ;% helicopterD4_P.HILInitialize_DOInitial
	  section.data(35).logicalSrcIdx = 108;
	  section.data(35).dtTransOffset = 34;
	
	  ;% helicopterD4_P.HILReadEncoderTimebase_Active
	  section.data(36).logicalSrcIdx = 109;
	  section.data(36).dtTransOffset = 35;
	
	  ;% helicopterD4_P.HILWriteAnalog_Active
	  section.data(37).logicalSrcIdx = 110;
	  section.data(37).dtTransOffset = 36;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helicopterD4_P.HILReadEncoderTimebase_Overflow
	  section.data(1).logicalSrcIdx = 111;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helicopterD4_B)
    ;%
      section.nData     = 17;
      section.data(17)  = dumData; %prealloc
      
	  ;% helicopterD4_B.TravelCounttorad
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_B.Gain
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helicopterD4_B.Sum4
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helicopterD4_B.Gain_d
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helicopterD4_B.PitchCounttorad
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helicopterD4_B.Gain_i
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helicopterD4_B.Gain_b
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% helicopterD4_B.ElevationCounttorad
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% helicopterD4_B.Gain_e
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% helicopterD4_B.Sum
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% helicopterD4_B.Gain_dg
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% helicopterD4_B.Gain1
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% helicopterD4_B.u
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 17;
	
	  ;% helicopterD4_B.Gain_l
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 19;
	
	  ;% helicopterD4_B.BackmotorSaturation
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 20;
	
	  ;% helicopterD4_B.FrontmotorSaturation
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 21;
	
	  ;% helicopterD4_B.In1
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 22;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 8;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (helicopterD4_DW)
    ;%
      section.nData     = 13;
      section.data(13)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% helicopterD4_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% helicopterD4_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% helicopterD4_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% helicopterD4_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% helicopterD4_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% helicopterD4_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% helicopterD4_DW.TimeStampA
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
	  ;% helicopterD4_DW.LastUAtTimeA
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 65;
	
	  ;% helicopterD4_DW.TimeStampB
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 66;
	
	  ;% helicopterD4_DW.LastUAtTimeB
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 67;
	
	  ;% helicopterD4_DW.HILWriteAnalog_Buffer
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 68;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 17;
      section.data(17)  = dumData; %prealloc
      
	  ;% helicopterD4_DW._PWORK.FilePtr
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_DW.FromWorkspace1_PWORK.TimePtr
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helicopterD4_DW.FromWorkspace_PWORK.TimePtr
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helicopterD4_DW._PWORK_l.FilePtr
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 3;
	
	  ;% helicopterD4_DW.Scope_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 4;
	
	  ;% helicopterD4_DW.e_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 5;
	
	  ;% helicopterD4_DW.p_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 7;
	
	  ;% helicopterD4_DW.ElevationScopedegs_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 22;
	  section.data(8).dtTransOffset = 9;
	
	  ;% helicopterD4_DW.ElevationScopedeg_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 23;
	  section.data(9).dtTransOffset = 10;
	
	  ;% helicopterD4_DW.PitchScopedeg_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 24;
	  section.data(10).dtTransOffset = 11;
	
	  ;% helicopterD4_DW.PtichrateScopedegs_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 25;
	  section.data(11).dtTransOffset = 12;
	
	  ;% helicopterD4_DW.PtichrateScopedegs1_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 26;
	  section.data(12).dtTransOffset = 13;
	
	  ;% helicopterD4_DW.TravelrateScopedegs_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 27;
	  section.data(13).dtTransOffset = 14;
	
	  ;% helicopterD4_DW.TravelScopedeg_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 28;
	  section.data(14).dtTransOffset = 15;
	
	  ;% helicopterD4_DW.Backmotor_PWORK.LoggedData
	  section.data(15).logicalSrcIdx = 29;
	  section.data(15).dtTransOffset = 16;
	
	  ;% helicopterD4_DW.Frontmotor_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 30;
	  section.data(16).dtTransOffset = 17;
	
	  ;% helicopterD4_DW.HILWriteAnalog_PWORK
	  section.data(17).logicalSrcIdx = 31;
	  section.data(17).dtTransOffset = 18;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 32;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 33;
	  section.data(2).dtTransOffset = 3;
	
	  ;% helicopterD4_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 34;
	  section.data(3).dtTransOffset = 11;
	
	  ;% helicopterD4_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 35;
	  section.data(4).dtTransOffset = 19;
	
	  ;% helicopterD4_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 36;
	  section.data(5).dtTransOffset = 27;
	
	  ;% helicopterD4_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 37;
	  section.data(6).dtTransOffset = 35;
	
	  ;% helicopterD4_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 38;
	  section.data(7).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% helicopterD4_DW._IWORK.Count
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_DW.FromWorkspace1_IWORK.PrevIndex
	  section.data(2).logicalSrcIdx = 41;
	  section.data(2).dtTransOffset = 1;
	
	  ;% helicopterD4_DW.FromWorkspace_IWORK.PrevIndex
	  section.data(3).logicalSrcIdx = 42;
	  section.data(3).dtTransOffset = 2;
	
	  ;% helicopterD4_DW._IWORK_b.Count
	  section.data(4).logicalSrcIdx = 43;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% helicopterD4_DW.If_ActiveSubsystem
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
	  ;% helicopterD4_DW.IfActionSubsystem_SubsysRanBC
	  section.data(2).logicalSrcIdx = 45;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2815837564;
  targMap.checksum1 = 4241144707;
  targMap.checksum2 = 2895534585;
  targMap.checksum3 = 2497324469;


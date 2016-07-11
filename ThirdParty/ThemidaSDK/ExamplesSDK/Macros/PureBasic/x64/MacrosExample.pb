;
; ------------------------------------------------------------
;
;   PureBasic - Usage of SecureEngine macros in PureBasic x64
;
;    (c) 2012 - Oreans Technologies
;
; ------------------------------------------------------------
;

XIncludeFile "SecureEngineMacrosX64.pb"


; Testing VM macro

VMStart()

MessageRequester("Macros Example", "Executing VM macro", 0)

VMEnd()


; Testing CodeReplace macro

CodeReplaceStart()

MessageRequester("Macros Example", "Executing CodeReplace macro", 0)

CodeReplaceEnd()


; Testing CheckProtection macro

MyCheckVar.l = 0

SECheckProtection(@MyCheckVar, 12345678)

If MyCheckVar <> 12345678 
  
  MessageRequester("Macros Example", "CheckProtection failed!", 0)  
  
Else 
  
  MessageRequester("Macros Example", "CheckProtection OK!", 0)    
  
EndIf




; IDE Options = PureBasic 4.61 (Windows - x64)
; CursorPosition = 34
; FirstLine = 1
; Executable = Example.exe
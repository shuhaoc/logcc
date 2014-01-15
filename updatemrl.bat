set MRL_ROOT=..\mrl
set PROJECT_ROOT=.

xcopy /e /y /i /f %MRL_ROOT%\include\mrl %PROJECT_ROOT%\include\mrl
xcopy /e /y /i /f %MRL_ROOT%\lib\Debug\*.lib %PROJECT_ROOT%\lib\Debug\
xcopy /e /y /i /f %MRL_ROOT%\bin\Debug\*.dll %PROJECT_ROOT%\bin\Debug\
xcopy /e /y /i /f %MRL_ROOT%\lib\Release\*.lib %PROJECT_ROOT%\lib\Release\
xcopy /e /y /i /f %MRL_ROOT%\bin\Release\*.dll %PROJECT_ROOT%\bin\Release\

pause
[Setup]
AppName=网狐6.6测试
AppVerName=视频升级
;不能选择安装路径
;安装路径从注册表读取
DisableDirPage        = yes
DefaultDirName={reg:HKCU\Software\WHQPGame\Plaza,Path}
OutputBaseFilename=UpGradeVD
Compression=zip
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp

[Files]
Source: "{app}\UpGradeVD.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{app}\UpGradeVD\Locker.bmp"; DestDir: "{app}\UpGradeVD"; Flags: ignoreversion
Source: "{app}\UpGradeVD\TableFrame.DAT"; DestDir: "{app}\UpGradeVD"; Flags: ignoreversion
Source: "{app}\UpGradeVD\TableNormal.bmp"; DestDir: "{app}\UpGradeVD"; Flags: ignoreversion
Source: "{app}\UpGradeVD\TablePlaying.bmp"; DestDir: "{app}\UpGradeVD"; Flags: ignoreversion
Source: "{app}\UpGradeVD\UserReady.bmp"; DestDir: "{app}\UpGradeVD"; Flags: ignoreversion

[Run]
Filename: "{app}\GamePlaza.exe"; Description: "{cm:LaunchProgram,视频升级}";

[CustomMessages]
default.NameAndVersion=%1 版本 %2
default.AdditionalIcons=附加快捷方式:
default.CreateDesktopIcon=创建桌面快捷方式(&D)
default.CreateQuickLaunchIcon=创建快速运行栏快捷方式(&Q)
default.ProgramOnTheWeb=%1 网站
default.UninstallProgram=卸载 %1
default.LaunchProgram=运行 %1
default.AssocFileExtension=将 %2 文件扩展名与 %1 建立关联(&A)
default.AssocingFileExtension=正在将 %2 文件扩展名与 %1 建立关联...

[Languages]
; These files are stubs
; To achieve better results after recompilation, use the real language files
Name: "default"; MessagesFile: "embedded\default.isl"; 

[Code]
//导入一个Windows API 函数
function MessageBox(hWnd: Integer; lpText, lpCaption: String; uType: Cardinal): Integer;
external 'MessageBoxA@user32.dll stdcall';

//安装完成后
//更新游戏列表
procedure CurStepChanged(CurStep: TSetupStep);
var
  hWnd: HWND;

begin
    if CurStep=ssDone   then
      begin
        hWnd := FindWindowByClassName('WHQPGamePlaza');

        if hWnd <> 0 then
          begin
              PostMessage(hWnd, 1124, 500, 0);
              //MessageBox(0, 'PostMessage(hWnd, 1124, 5, 0);', 'MessageBox', MB_OK);
          end
     end
end;

//------------------------------------------------
//                   the end
//-------------------------------------------------

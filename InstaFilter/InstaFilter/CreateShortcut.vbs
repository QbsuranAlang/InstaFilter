set WshShell = WScript.CreateObject("WScript.Shell" )
strDesktop = WshShell.SpecialFolders("AllUsersDesktop" )
set oShellLink = WshShell.CreateShortcut(strDesktop & "\InstaFilter.lnk" )
oShellLink.TargetPath = (WshShell.CurrentDirectory & "\InstaFilter.exe")
oShellLink.WindowStyle = 1
oShellLink.IconLocation = (WshShell.CurrentDirectory & "\InstaFilter.exe")
oShellLink.Description = "InstaFilter.exe"
oShellLink.WorkingDirectory = (WshShell.CurrentDirectory)
oShellLink.Save
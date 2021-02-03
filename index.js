let GotoSleep;

const exec = require('child_process').exec; 
const runCommand = function(str) {
  return exec(str).stderr.pipe(process.stderr);
};

if ( process.platform == 'win32' || process.platform === 'darwin' ) {
  GotoSleep = require('bindings')('GotoSleep');
}
// else if ( process.platform === 'darwin' ) {
//   GotoSleep = require('bindings')('GotoSleep');
//   // hack screen locking for OSX
//   GotoSleep.lockScreen = function() {
//     runCommand('/System/Library/CoreServices/Menu\\ Extras/User.menu/Contents/Resources/CGSession -suspend');
//   }
// }
else {
  const which = require('which');
  const handler = function() {
    if ( which.sync("xdg-screensaver", { nothrow: true }) ) {
      runCommand("xdg-screensaver lock");
    }
    else if ( which.sync("gnome-screensaver-command", { nothrow: true }) ) {
      runCommand("gnome-screensaver-command -l");
    }
    else {
      //
      // try some random things
      //
      if ( which.sync("dbus-send", { nothrow: true }) ) {
        runCommand("dbus-send --type=method_call --dest=org.gnome.ScreenSaver /org/gnome/ScreenSaver org.gnome.ScreenSaver.Lock");
      }
      if ( which.sync("xset", { nothrow: true }) ) {
        runCommand("xset dpms force suspend");
      }
    }
  };

  GotoSleep = {
    gotoSleep: handler,
    lockScreen: handler
  };
}
module.exports = GotoSleep;
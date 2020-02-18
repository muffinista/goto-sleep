{
  "targets": [
    {
      "target_name": "GotoSleep",
      "sources": [ "GotoSleep.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      'cflags': [
        '-Wall',
        '-Wparentheses',
        '-Winline',
        '-Wbad-function-cast',
        '-Wdisabled-optimization'
      ],
      'conditions': [
        ['OS == "mac"', {
          'defines': ['IS_MAC'],
          'include_dirs': [
            'System/Library/Frameworks/Carbon.Framework/Headers'
          ],
          'link_settings': {
            'libraries': [
              '-framework Carbon',
              '-framework AppKit',
            ]
          },
          'xcode_settings': {
            'OTHER_CFLAGS': [
                '-ObjC++'
            ]
          }
        }],
        ["OS=='win'", {
          'defines': ['IS_WINDOWS']
        }]
      ]
    }
  ]
}

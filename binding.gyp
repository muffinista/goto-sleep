{
  "targets": [
    {
      "target_name": "GotoSleep",
      "sources": [ "src/GotoSleep.cc" ],
      'cflags': [
        '-Wall',
        '-Wparentheses',
        '-Winline',
        '-Wbad-function-cast',
        '-Wdisabled-optimization'
      ],
      'conditions': [
        ['OS == "mac"', {
          'sources': [
            'src/mac/gotosleep.mm'
          ],
          'include_dirs': [
            'System/Library/Frameworks/Carbon.Framework/Headers'
          ],
          'link_settings': {
            'libraries': [
              '-framework Carbon',
              '-framework AppKit',
              '-F /System/Library/PrivateFrameworks',
              '-framework login'
            ]
          },
          'xcode_settings': {
            'OTHER_CFLAGS': [
                '-ObjC++'
            ]
          }
        }],
        ["OS=='win'", {
          'sources': [
            'src/win/gotosleep.cc'
          ]
        }]
      ]
    }
  ]
}

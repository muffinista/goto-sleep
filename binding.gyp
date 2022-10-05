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
        '-Wdisabled-optimization',
        '-std=c++17'
      ],
      'cflags_cc': [
        '-std=c++17'
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
              '/System/Library/PrivateFrameworks/login.framework/Versions/Current/login'
            ]
          },
          'xcode_settings': {
            'OTHER_CFLAGS': [
                '-ObjC++'
            ]
          }
        }],
        ["OS=='win'", {
          'defines': ['IS_WINDOWS'],
          'msvs_settings': {
            'VCCLCompilerTool': { "ExceptionHandling": 1, 'AdditionalOptions': [ '-std:c++17' ] }
          }
        }]
      ]
    }
  ]
}

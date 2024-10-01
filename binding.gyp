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
        '-Wdisabled-optimization',
        '-std=c++20'
      ],
      'cflags_cc': [
        '-std=c++20'
      ],
      'conditions': [
        ['OS == "mac"', {
          'sources': [
            'src/mac/gotosleep.mm'
          ],
          'link_settings': {
            'libraries': [
              '-F /System/Library/PrivateFrameworks',
              '-framework login'
            ]
          }
        }],
        ["OS=='win'", {
          'defines': ['IS_WINDOWS'],
          'msvs_settings': {
            'VCCLCompilerTool': { "ExceptionHandling": 1, 'AdditionalOptions': [ '-std:c++20' ] }
          },
          'sources': [
            'src/win/gotosleep.cc'
          ]
        }]
      ]
    }
  ]
}

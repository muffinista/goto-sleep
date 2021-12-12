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
          'link_settings': {
            'libraries': [
            '-framework login',
            '-F /System/Library/PrivateFrameworks'
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

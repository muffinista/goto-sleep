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
          'link_settings': {
            'libraries': [
              '-F /System/Library/PrivateFrameworks',
              '-framework login'
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

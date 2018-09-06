// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class PlatformChannel extends StatefulWidget {
  @override
  _PlatformChannelState createState() => new _PlatformChannelState();
}

class _PlatformChannelState extends State<PlatformChannel> {
  MethodChannel jsonChannel = MethodChannel('cppplugins.flutter.io/json_plugin',JSONMethodCodec());
  MethodChannel standardChannel = MethodChannel('cppplugins.flutter.io/standard_plugin'); 


  String _batteryLevel = 'Battery level: unknown.';
  String _chargingStatus = 'Battery status: unknown.';

  Future<Null> _testChannel() async {
      {
        final String strResult = await jsonChannel.invokeMethod('testString','world');
        
        print('invoke json string result $strResult');

        final int intResult = await jsonChannel.invokeMethod('testInt',123456);

        print('invoke json int result $intResult');

      }

      {
        final String strResult = await standardChannel.invokeMethod('testString','world');

        print('invoke standard string result $strResult');

        final int intResult = await standardChannel.invokeMethod('testInt',123456);

        print('invoke standard int result $intResult');
      }

  }

  @override
  void initState() {
    super.initState();

    jsonChannel.setMethodCallHandler((MethodCall call){
      print("call from json plugin method ${call.method} arguments ${call.arguments}");
    });

    standardChannel.setMethodCallHandler((MethodCall call){
      print("call from standard plugin method ${call.method} arguments ${call.arguments}");
    });
  }


  @override
  Widget build(BuildContext context) {
    return new Material(
      child: new Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          new Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: <Widget>[
              new Text(_batteryLevel),
              new Padding(
                padding: const EdgeInsets.all(16.0),
                child: new RaisedButton(
                  child: const Text('test plugin'),
                  onPressed: _testChannel,
                  elevation: 2.0,
                ),
              ),
            ],
          ),
          new Text(_chargingStatus),
        ],
      ),
    );
  }
}

void main() {
  runApp(new MaterialApp(home: new PlatformChannel()));
}

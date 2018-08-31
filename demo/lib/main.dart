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
  static const MethodChannel methodChannel =
      const MethodChannel('cppplugins.flutter.io/test_plugin',JSONMethodCodec());
  static const EventChannel eventChannel =
      const EventChannel('cppplugins.flutter.io/test_plugin',JSONMethodCodec());

  String _batteryLevel = 'Battery level: unknown.';
  String _chargingStatus = 'Battery status: unknown.';

  Future<Null> _getBatteryLevel() async {
    String batteryLevel;
    try {
      final String result = await methodChannel.invokeMethod('hello');
      batteryLevel = 'Battery level: $result';


    } on PlatformException {
      batteryLevel = 'Failed to get battery level.';
    }
    setState(() {
      _batteryLevel = batteryLevel;
    });
  }

  @override
  void initState() {
    super.initState();

    methodChannel.setMethodCallHandler((MethodCall call){
      print("call from cpp plugin");
      print(call.method);
      print(call.arguments);
    });

    //eventChannel.receiveBroadcastStream().listen(_onEvent, onError: _onError);
  }

  void _onEvent(Object event) {
    setState(() {
      _chargingStatus =
          "Battery status: ${event == 'test' ? '' : 'dis'}charging.";
    });
  }

  void _onError(Object error) {
    setState(() {
      _chargingStatus = 'Battery status: unknown.';
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
            children: <Widget>[
              new Text(_batteryLevel, key: const Key('Battery level label')),
              new Padding(
                padding: const EdgeInsets.all(16.0),
                child: new RaisedButton(
                  child: const Text('Refresh'),
                  onPressed: _getBatteryLevel,
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

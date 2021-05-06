import 'package:flutter/material.dart';
import 'package:rplayer/rplayer.dart';

class VideoTestPage extends StatefulWidget {
  @override
  _VideoTestPageState createState() => _VideoTestPageState();
}

class _VideoTestPageState extends State<VideoTestPage> {
  final player = RPlayer(
    config: RPlayerConfig()
      ..retryTimesOnDisconnect = 10
      ..retryDelayInMilliseconds = 2000,
  );
  final player2 = RPlayer(
    config: RPlayerConfig()
      ..retryTimesOnDisconnect = 10
      ..retryDelayInMilliseconds = 2000,
  );

  @override
  void initState() {
    super.initState();
    player.startPlayWhenReady('rtsp://admin:admin@192.168.1.103:8554/live');
    player2.startPlayWhenReady('rtsp://admin:admin@192.168.1.102:8554/live');
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('RPlayer Video Test Page'),
      ),
      body: ListView(
        shrinkWrap: true,
        children: [
          RPlayerView(
            player: player,
            width: MediaQuery.of(context).size.width,
            height: 300,
          ),
          RPlayerView(
            player: player2,
            width: MediaQuery.of(context).size.width,
            height: 300,
          ),
        ],
      ),
    );
  }
}

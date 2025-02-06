import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  TextEditingController ipController = TextEditingController();
  String relayStatus = "Unknown";

  Future<void> sendCommand(String command) async {
    if (ipController.text.isEmpty) {
      return;
    }
    String url = "http://${ipController.text}/relay/$command";
    try {
      var response = await http.get(Uri.parse(url));
      if (response.statusCode == 200) {
        setState(() {
          relayStatus = command.toUpperCase();
        });
      }
    } catch (e) {
      print("Error: $e");
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: Text("Basic Home Automation")),
        body: Padding(
          padding: EdgeInsets.all(20),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              TextField(
                controller: ipController,
                decoration: InputDecoration(
                  labelText: "Enter ESP8266 IP Address",
                  border: OutlineInputBorder(),
                ),
              ),
              SizedBox(height: 20),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  ElevatedButton(
                    onPressed: () => sendCommand("on"),
                    child: Text("Relay ON"),
                  ),
                  ElevatedButton(
                    onPressed: () => sendCommand("off"),
                    child: Text("Relay OFF"),
                  ),
                ],
              ),
              SizedBox(height: 20),
              Text("Relay Status: $relayStatus",
                  style: TextStyle(fontSize: 18)),
            ],
          ),
        ),
      ),
    );
  }
}

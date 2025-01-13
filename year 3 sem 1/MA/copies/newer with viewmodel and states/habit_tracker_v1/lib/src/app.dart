import 'package:flutter/material.dart';
import 'package:habit_tracker_v1/src/screens/add_habit_screen.dart';
import 'package:habit_tracker_v1/src/screens/home_screen.dart';
// import 'package:habit_tracker_v1/src/viewmodel/habit_viewmodel.dart';
// import 'package:provider/provider.dart';


// DEPRECATED: everything is now done in the `main.dart` file

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Habit Tracker',
      theme: ThemeData(
            primarySwatch: Colors.blue,
            brightness: Brightness.light,
          ),
          darkTheme: ThemeData(
            primarySwatch: Colors.blue,
            brightness: Brightness.dark,
      ),
      home: const HomeScreen(),
      routes: {
        '/add': (context) => const AddHabitScreen(),
      },
    );
  }
}

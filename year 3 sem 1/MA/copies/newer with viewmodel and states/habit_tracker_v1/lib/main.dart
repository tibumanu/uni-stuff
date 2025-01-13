import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import 'src/screens/home_screen.dart';
import 'src/viewmodel/habit_viewmodel.dart';

void main() {
  runApp(
    // Wrap the app with Provider so that HabitViewModel is available
    ChangeNotifierProvider(
      create: (_) => HabitViewModel()..loadHabits(),
      child: MyApp(),
    ),
  );
}


class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

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
    );
  }
}

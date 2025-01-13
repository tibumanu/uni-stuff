import 'package:flutter/material.dart';
import '../model/habit.dart';

class ViewHabitScreen extends StatelessWidget {
  final Habit habit;

  const ViewHabitScreen({Key? key, required this.habit}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(habit.name),
      ),
      body: Container(
        decoration: const BoxDecoration(
          gradient: LinearGradient(
            colors: [ Color.fromARGB(255, 40, 27, 79), Color.fromARGB(255, 27, 37, 61),],
            begin: Alignment.topCenter,
            end: Alignment.bottomCenter,
          ),
        ),
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              Card(
                elevation: 8,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ),
                child: SingleChildScrollView(
                  padding: const EdgeInsets.all(16.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      _buildHabitDetail(Icons.description, 'Description', habit.description ?? 'No description'),
                      _buildHabitDetail(Icons.category, 'Type', habit.type),
                      _buildHabitDetail(Icons.repeat, 'Frequency', habit.frequency),
                      _buildHabitDetail(Icons.label, 'Label', habit.label),
                      if (habit.target != null) _buildHabitDetail(Icons.track_changes, 'Target', habit.target!),
                      _buildHabitDetail(Icons.access_time_rounded, 'Added at', habit.createdAt.toString()),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }

   Widget _buildHabitDetail(IconData icon, String title, String detail) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 8.0),
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Icon(icon, color: const Color.fromARGB(255, 64, 86, 119)),
          const SizedBox(width: 16),
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  title,
                  style: const TextStyle(fontWeight: FontWeight.bold, color: Color.fromARGB(255, 104, 126, 159)),
                ),
                const SizedBox(height: 4),
                Text(detail, style: const TextStyle(fontSize: 16)),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
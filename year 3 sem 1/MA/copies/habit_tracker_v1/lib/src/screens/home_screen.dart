import 'package:flutter/material.dart';
import '../model/habit.dart';
import 'add_habit_screen.dart';
import 'view_habit_screen.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({Key? key}) : super(key: key);

  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  List<Habit> habits = [
    Habit(
      id: 1,
      name: 'Exercise',
      type: 'GOOD',
      description: 'Running, cycling or some other physical activity',
      frequency: 'daily',
      label: 'wellness',
      target: '45 minutes',
      createdAt: DateTime.parse('2024-12-01 00:00:00Z'),
    ),
    Habit(
      id: 2,
      name: 'Smoking',
      type: 'BAD',
      description: 'Avoid smoking cigarettes or using tobacco products',
      frequency: 'daily',
      label: 'health',
      target: 'zero tobacco',
      createdAt: DateTime.parse('2024-12-01 00:00:02Z'),
    ),
    Habit(
      id: 3,
      name: 'Reading',
      type: 'GOOD',
      description: 'Read a book, article or blog post',
      frequency: 'daily',
      label: 'learning',
      target: '45 minutes',
      createdAt: DateTime.parse('2024-12-01 00:00:05Z'),
    ),
    Habit(
      id: 4,
      name: 'Water intake',
      type: 'GOOD',
      description: 'Drink water to stay hydrated',
      frequency: 'daily',
      label: 'health',
      target: '2L/8 glasses',
      createdAt: DateTime.parse('2024-12-01 00:00:06Z'),
    ),
    Habit(
      id: 5,
      name: 'Meditation',
      type: 'GOOD',
      description: 'Practice mindfulness: mind relaxation and focus',
      frequency: 'daily',
      label: 'wellness',
      target: '20 minutes',
      createdAt: DateTime.parse('2024-12-01 00:00:07Z'),
    ),
  ];


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Habit Tracker'),
      ),
      body: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 8.0), // Add horizontal padding
        child: ListView.builder(
          itemCount: habits.length,
          itemBuilder: (context, index) {
        final habit = habits[index];
        return Card(
          margin: const EdgeInsets.symmetric(vertical: 8.0), // Add vertical margin
          child: ListTile(
            contentPadding: const EdgeInsets.symmetric(vertical: 12.0, horizontal: 12.0), // Add vertical padding
            title: Text(habit.name),
            subtitle: Text(habit.description ?? '', style: const TextStyle(fontSize: 12)),
            leading: SizedBox(
          width: 42, 
          child: Text(
            habit.label,
            style: const TextStyle(
              fontStyle: FontStyle.italic,
              fontWeight: FontWeight.bold,
            ),
            overflow: TextOverflow.ellipsis,
          ),
            ),
            // also show the frequency and target, smaller font and grey color
            trailing: Text(
              '${habit.frequency} \n ${habit.target ?? ''}', 
              style: const TextStyle(fontSize: 12, color: Colors.grey),
              textAlign: TextAlign.right,
            ),
            onTap: () {
          Navigator.push(
            context,
            MaterialPageRoute(
              builder: (context) => ViewHabitScreen(habit: habit),
            ),
          );
            },
            onLongPress: () {
          showModalBottomSheet(
            context: context, 
            builder: (context) => _buildBottomSheet(context, habit),
            shape: const RoundedRectangleBorder(
              borderRadius: BorderRadius.vertical(top: Radius.circular(25), bottom: Radius.circular(25)),

            ));
            },
          ),
        );
          },
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          final newHabit = await Navigator.push<Habit>(
            context,
            MaterialPageRoute(builder: (context) => const AddHabitScreen()),
          );
          if (newHabit != null) {
            setState(() {
              habits.add(newHabit);
            });
          }
        },
        child: const Icon(Icons.add),
      ),
    );
  }

Widget _buildBottomSheet(BuildContext context, Habit habit) {
    return Padding(
      padding: const EdgeInsets.only(bottom: 20), // Added bottom padding
      child: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          ListTile(
            leading: const Icon(Icons.edit),
            title: const Text('Update'),
            onTap: () async {
              Navigator.pop(context);
              final updatedHabit = await Navigator.push<Habit>(
                context,
                MaterialPageRoute(
                  builder: (context) => AddHabitScreen(habit: habit),
                ),
              );
              if (updatedHabit != null) {
                setState(() {
                  final index = habits.indexOf(habit);
                  habits[index] = updatedHabit;
                });
              }
            },
          ),
          ListTile(
            leading: const Icon(Icons.delete, color: Colors.red),
            title: const Text('Delete', style: TextStyle(color: Colors.red)),
            onTap: () {
              Navigator.pop(context);
              showDialog(
                context: context,
                builder: (BuildContext context) {
                  return AlertDialog(
                    title: const Text('Delete Habit'),
                    content: const Text('Are you sure you want to delete this habit?'),
                    actions: <Widget>[
                      TextButton(
                        onPressed: () {
                          Navigator.of(context).pop();
                        },
                        child: const Text('Cancel'),
                      ),
                      TextButton(
                        onPressed: () {
                          setState(() {
                            habits.remove(habit);
                          });
                          Navigator.of(context).pop();
                        },
                        child: const Text('Delete', style: TextStyle(color: Colors.red)),
                      ),
                    ],
                  );
                },
              );
            },
          ),
        ],
      ),
    );
  }



  void _confirmDelete(BuildContext context, Habit habit) {
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Confirm Delete'),
        content: const Text('Are you sure you want to delete this habit?'),
        actions: [
          TextButton(
            onPressed: () {
              Navigator.pop(context);
            },
            child: const Text('Cancel'),
          ),
          TextButton(
            onPressed: () {
              Navigator.pop(context);
              setState(() {
                habits.remove(habit);
              });
            },
            child: const Text('Delete', style: TextStyle(color: Colors.red)),
          ),
        ],
      ),
    );
  }
}



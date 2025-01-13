import 'package:flutter/material.dart';
import '../model/habit.dart';

class HabitViewModel extends ChangeNotifier {
  List<Habit> _habits = [];
  List<Habit> get habits => _habits;

  void addHabit(Habit habit) {
    _habits.add(habit);
    notifyListeners();
  }

  void updateHabit(Habit updatedHabit) {
    final index = _habits.indexWhere((habit) => habit.id == updatedHabit.id);
    if (index != -1) {
      _habits[index] = updatedHabit;
      notifyListeners();
    }
  }

  void deleteHabit(Habit habit) {
    _habits.remove(habit);
    notifyListeners();
  }

  void loadHabits() {
    _habits = [
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
    notifyListeners();
  }
}

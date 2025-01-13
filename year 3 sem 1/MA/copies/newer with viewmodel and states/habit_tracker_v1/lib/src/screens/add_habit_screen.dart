import 'package:flutter/material.dart';
import 'package:habit_tracker_v1/src/model/habit.dart';
import 'package:provider/provider.dart';

import '../viewmodel/habit_viewmodel.dart';

class AddHabitScreen extends StatefulWidget {
  const AddHabitScreen({Key? key, this.habit}) : super(key: key);
  final Habit? habit;

  @override
  _AddHabitScreenState createState() => _AddHabitScreenState();
}

class _AddHabitScreenState extends State<AddHabitScreen> {
  final _formKey = GlobalKey<FormState>();
  late String name;
  late String type;
  String? description;
  late String frequency;
  late String label;
  String? target;

  @override
  void initState() {
    super.initState();
    if (widget.habit != null) {
      name = widget.habit!.name;
      type = widget.habit!.type;
      description = widget.habit!.description;
      frequency = widget.habit!.frequency;
      label = widget.habit!.label;
      target = widget.habit!.target;
    } else {
      name = '';
      type = '';
      description = '';
      frequency = 'daily';
      label = '';
      target = '';
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.habit == null ? 'Add Habit' : 'Edit Habit'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: SingleChildScrollView(
          child: Form(
            key: _formKey,
            child: Card(
              elevation: 8,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(12),
              ),
              child: Padding(
                padding: const EdgeInsets.all(26.0),
                child: Column(
                  children: [
                    TextFormField(
                      decoration: InputDecoration(
                        labelText: 'name',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(8),
                        ),
                      ),
                      initialValue: name,
                      onChanged: (value) => name = value,
                      validator: (value) {
                        if (value == null || value.isEmpty) {
                          return 'Name is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 16),

                    DropdownButtonFormField(
                      // choose between "GOOD", "NEITHER" and "BAD"
                      // set the value to the selected item
                      value: type == '' ? null : type,
                      decoration: InputDecoration(
                        labelText: 'type',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                        borderRadius: BorderRadius.circular(8)
                        ),
                      ),
                      items: const [
                        DropdownMenuItem(
                          value: 'GOOD',
                          child: Text('GOOD'),
                        ),
                        DropdownMenuItem(
                          value: 'NEITHER',
                          child: Text('NEITHER'),
                        ),
                        DropdownMenuItem(
                          value: 'BAD',
                          child: Text('BAD'),
                        ),
                      ],
                      onChanged: (value) {
                        setState(() {
                          type = value.toString();
                        });
                      },
                      validator: (value) {
                        if (value == null) {
                          return 'Type is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 16),

                    // Description Field
                    TextFormField(
                      decoration: InputDecoration(
                        labelText: 'description',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(8),
                        ),
                      ),
                      initialValue: description,
                      onChanged: (value) => description = value,
                      validator: (value) {
                        if (value != null && value.length > 100) {
                          return 'Description must be less than 100 characters';
                        } else if (value == null || value.isEmpty) {
                          return 'Description is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 16),

                    // Frequency Field
                    TextFormField(
                      decoration: InputDecoration(
                        labelText: 'frequency',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(8),
                        ),
                      ),
                      initialValue: frequency,
                      onChanged: (value) => frequency = value,
                      validator: (value) {
                        if (value == null || value.isEmpty) {
                          return 'Frequency is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 16),

                    // Label Field
                    TextFormField(
                      decoration: InputDecoration(
                        labelText: 'label',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(8),
                        ),
                      ),
                      initialValue: label,
                      onChanged: (value) => label = value,
                      validator: (value) {
                        if (value == null || value.isEmpty) {
                          return 'Label is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 16),

                    // Target Field
                    TextFormField(
                      decoration: InputDecoration(
                        labelText: 'target',
                        filled: false,
                        fillColor: Colors.grey[200],
                        border: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(8),
                        ),
                      ),
                      initialValue: target,
                      onChanged: (value) => target = value,
                      validator: (value) {
                        if (value != null && value.length > 100) {
                          return 'Target must be less than 100 characters';
                        } else if (value == null || value.isEmpty) {
                          return 'Target is required';
                        }
                        return null;
                      },
                    ),
                    const SizedBox(height: 20),

                    ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        shadowColor: Colors.blueGrey[900],
                        backgroundColor: const Color.fromARGB(255, 25, 31, 41),
                        foregroundColor: Colors.grey[200],
                      ),
                      
                      onPressed: () {
                        if (_formKey.currentState!.validate()) {
                          _formKey.currentState!.save();
                          final newHabit = Habit(
                            id: widget.habit?.id ?? DateTime.now().millisecondsSinceEpoch,
                            name: name,
                            type: type,
                            description: description,
                            frequency: frequency,
                            label: label,
                            target: target,
                            createdAt: widget.habit?.createdAt ?? DateTime.now(),
                          );
                          final habitViewModel = Provider.of<HabitViewModel>(context, listen: false);


                          if (widget.habit == null) {
                            habitViewModel.addHabit(newHabit);
                          } else {
                            habitViewModel.updateHabit(newHabit);
                          }
                          Navigator.pop(context);
                        }
                      },
                      child: const Text('Save'),
                    ),
                  ],
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}

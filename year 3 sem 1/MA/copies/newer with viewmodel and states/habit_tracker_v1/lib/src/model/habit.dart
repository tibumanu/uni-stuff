class Habit {
  final int id;
  final String name;
  final String type;
  final String? description;
  final String frequency;
  final String label;
  final String? target;
  final DateTime createdAt;

  Habit({
    required this.id,
    required this.name,
    required this.type,
    this.description,
    required this.frequency,
    required this.label,
    this.target,
    required this.createdAt,
  });
}
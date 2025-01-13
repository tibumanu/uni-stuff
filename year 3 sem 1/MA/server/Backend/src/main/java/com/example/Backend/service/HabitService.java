package com.example.Backend.service;

import com.example.Backend.model.Habit;
import jakarta.transaction.Transactional;

import java.util.List;

public interface HabitService {
    List<Habit> getHabits();
    @Transactional
    Habit getHabitById(Long id);
    @Transactional
    Habit addHabit(Habit habit);
    @Transactional
    Habit updateHabit(Habit habit);
    @Transactional
    void deleteHabit(Long id);
}

package com.example.Backend.repository;

import com.example.Backend.model.Habit;
import io.swagger.v3.oas.annotations.Hidden;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@Hidden
public interface HabitRepository extends JpaRepository<Habit, Long> {
    public List<Habit> findAll();
    public Optional<Habit> findHabitById(Long id);
    public Optional<Habit> findHabitByNameLike(String name);
    public List<Habit> findHabitsByType(String type);
    public List<Habit> findHabitsByFrequency(String frequency);
}

package com.example.Backend.service;

import com.example.Backend.model.Habit;
import com.example.Backend.repository.HabitRepository;
import jakarta.persistence.EntityNotFoundException;
import jakarta.transaction.Transactional;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;

@RequiredArgsConstructor
@Service
public class HabitServiceImpl implements HabitService {
    private final HabitRepository habitRepository;


    @Override
    public List<Habit> getHabits() {
        return habitRepository.findAll();
    }

    @Override
    public Habit getHabitById(Long id) {
        return habitRepository.findById(id).orElseThrow(
                () -> new EntityNotFoundException(String.format("Habit with id %d not found", id))
        );
    }

    @Override
    @Transactional
    public Habit addHabit(Habit habit) {
        if(habit == null) {
            throw new IllegalArgumentException("Habit cannot be null");
        }
        if(habit.getCreatedAt() == null) {
            habit.setCreatedAt(LocalDateTime.now());
        }
        return habitRepository.save(habit);
    }

    @Override
    @Transactional
    public Habit updateHabit(Habit habit) {
        var updatedHabit = habitRepository.findById(habit.getId()).orElseThrow(
                () -> new EntityNotFoundException(String.format("Habit with id %d not found", habit.getId()))
        );
        updatedHabit.setName(habit.getName());
        updatedHabit.setLabel(habit.getLabel());
        updatedHabit.setDescription(habit.getDescription());
        updatedHabit.setDescription(habit.getDescription());
        updatedHabit.setFrequency(habit.getFrequency());
        updatedHabit.setTarget(habit.getTarget());
        updatedHabit.setCreatedAt(habit.getCreatedAt());

        return habitRepository.save(updatedHabit);
    }

    @Override
    @Transactional
    public void deleteHabit(Long id) {
        try{
            habitRepository.deleteById(id);
        } catch (Exception e) {
            throw new EntityNotFoundException(String.format("Habit with id %d not found", id));
        }
    }
}

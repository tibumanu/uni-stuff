package com.example.Backend.controller;

import com.example.Backend.converter.HabitDtoConverter;
import com.example.Backend.dto.AddHabitDto;
import com.example.Backend.dto.HabitDto;
import com.example.Backend.dto.Result;
import com.example.Backend.model.Habit;
import com.example.Backend.service.HabitService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("/habits")
public class HabitController {
    private final HabitService habitService;
    private final HabitDtoConverter habitDtoConverter;
    private final SimpMessagingTemplate messagingTemplate;

    @GetMapping
    public Result<List<HabitDto>> getHabits() {
        List<Habit> habits = habitService.getHabits();
        List<HabitDto> habitDtos = habits.stream()
                .map(habitDtoConverter::createFromEntity)
                .toList();
        return new Result<>(true, HttpStatus.OK.value(), "Retrieved all habits", habitDtos);
    }

    @GetMapping("/{habitId}")
    public Result<HabitDto> getHabitById(@PathVariable Long habitId) {
        Habit habit = habitService.getHabitById(habitId);
        HabitDto habitDto = habitDtoConverter.createFromEntity(habit);
        return new Result<>(true, HttpStatus.OK.value(), "Retrieved habit", habitDto);
    }

    @PostMapping
    public Result<HabitDto> addHabit(@RequestBody AddHabitDto addHabitDto) {
        Habit habit = habitDtoConverter.createFromAddHabitDto(addHabitDto);
        HabitDto habitDto = habitDtoConverter.createFromEntity(habitService.addHabit(habit));
        messagingTemplate.convertAndSend("/topic/habits", habitDto);
        return new Result<>(true, HttpStatus.OK.value(), "Habit added successfully", habitDto);
    }

    @PutMapping("/{habitId}")
    public Result<HabitDto> updateHabit(@PathVariable Long habitId, @RequestBody AddHabitDto addHabitDto) {
        Habit habit = habitDtoConverter.createFromAddHabitDto(addHabitDto);
        habit.setId(habitId);
        Habit updatedHabit = habitService.updateHabit(habit);
        HabitDto habitDto = habitDtoConverter.createFromEntity(updatedHabit);
        messagingTemplate.convertAndSend("/topic/habits", habitDto);
        return new Result<>(true, HttpStatus.OK.value(), "Habit updated successfully", habitDto);
    }

    @DeleteMapping("/{habitId}")
    public Result<Habit> deleteHabit(@PathVariable Long habitId) {
        habitService.deleteHabit(habitId);
        messagingTemplate.convertAndSend("/topic/habits/delete", habitId);
        return new Result<>(true, HttpStatus.OK.value(), "Habit deleted successfully", null);
    }

}

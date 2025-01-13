package com.example.Backend.dto;

import java.time.LocalDateTime;

/*
Habit class:
    private Long id;
    private String name;
    private String type;
    private String description;
    private String frequency;
    private String label;
    private String target;
    private LocalDateTime createdAt;
 */
public record HabitDto(
        Long id,
        String name,
        String description,
        String type,
        String frequency,
        String label,
        String target,
        LocalDateTime createdAt

) {
}

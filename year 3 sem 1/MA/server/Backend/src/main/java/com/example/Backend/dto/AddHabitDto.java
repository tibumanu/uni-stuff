package com.example.Backend.dto;

public record AddHabitDto(
        String name,
        String description,
        String type,
        String frequency,
        String label,
        String target
) {
}

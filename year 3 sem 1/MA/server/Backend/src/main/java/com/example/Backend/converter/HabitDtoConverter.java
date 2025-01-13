package com.example.Backend.converter;

import com.example.Backend.dto.AddHabitDto;
import com.example.Backend.dto.HabitDto;
import com.example.Backend.model.Habit;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;

@Component
@RequiredArgsConstructor
public class HabitDtoConverter implements Converter<Habit, HabitDto> {

    @Override
    public Habit createFromDto(HabitDto dto) {
        return Habit.builder()
                .id(dto.id())
                .name(dto.name())
                .description(dto.description())
                .type(dto.type())
                .frequency(dto.frequency())
                .label(dto.label())
                .target(dto.target())
                .createdAt(dto.createdAt())
                .build();
    }

    @Override
    public HabitDto createFromEntity(Habit entity) {
        return new HabitDto(
                entity.getId(),
                entity.getName(),
                entity.getDescription(),
                entity.getType(),
                entity.getFrequency(),
                entity.getLabel(),
                entity.getTarget(),
                entity.getCreatedAt()
        );
    }

    public Habit createFromAddHabitDto(AddHabitDto dto) {
        return Habit.builder()
                .name(dto.name())
                .description(dto.description())
                .type(dto.type())
                .frequency(dto.frequency())
                .label(dto.label())
                .target(dto.target())
                .createdAt(LocalDateTime.now())
                .build();
    }
}

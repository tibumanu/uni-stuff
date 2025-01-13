package com.example.Backend.controller;

import com.example.Backend.dto.HabitDto;
import com.example.Backend.dto.Result;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequiredArgsConstructor
@RequestMapping("/api")
public class ServerStatusController {
    @GetMapping("/status")
    public Result<List<HabitDto>> getAllHabits() {
        return new Result<>(true, HttpStatus.OK.value(), "Retrieved all habits", null);
    }
}

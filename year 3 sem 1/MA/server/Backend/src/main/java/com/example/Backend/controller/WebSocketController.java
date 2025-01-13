package com.example.Backend.controller;

import com.example.Backend.dto.HabitDto;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Controller;

@Controller
public class WebSocketController {

    @MessageMapping("/habit/update")
    @SendTo("/topic/habits")
    public HabitDto sendHabitUpdate(HabitDto habitDto) {
        return habitDto; // This will be broadcast to subscribers
    }
}

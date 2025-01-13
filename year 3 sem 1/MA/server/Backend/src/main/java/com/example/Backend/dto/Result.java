package com.example.Backend.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class Result<T> {
    private boolean flag; // Two values: true means success, false means failure.
    private Integer code; //Status code, e.g. 200;
    private String message; // Response message
    private T data; // The response payload

    public Result(boolean flag, Integer code, String message) {
    }

}
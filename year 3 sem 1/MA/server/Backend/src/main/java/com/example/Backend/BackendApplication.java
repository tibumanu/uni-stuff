package com.example.Backend;

import com.example.Backend.model.Habit;
import com.example.Backend.repository.HabitRepository;
import com.example.Backend.service.HabitService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableAsync;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@SpringBootApplication
@EnableTransactionManagement
@EnableAsync
public class BackendApplication implements CommandLineRunner {
	@Autowired
	private HabitRepository habitRepository;
	@Autowired
	private HabitService habitService;

	public static void main(String[] args) {
		SpringApplication.run(BackendApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
		if(habitRepository.count() == 0)		addHabits();
		List<Habit> habits = habitService.getHabits();
		for(Habit habit : habits){
			System.out.println(habit.toString());
		}
	}

	private void addHabits(){
		// smoking, drinking, exercise, reading, water intake, meditation, journaling
		List<String> habitNames = Arrays.asList("Smoking", "Drinking", "Exercise", "Reading", "Water Intake", "Meditation", "Journaling");
		Habit smoking = new Habit();
		smoking.setName("Smoking");
		smoking.setDescription("Avoid cigarettes or any other form of tobacco");
		smoking.setFrequency("Daily");
		smoking.setLabel("Health");
		smoking.setType("BAD");
		smoking.setTarget("0 cigarettes");
		habitService.addHabit(smoking);

		Habit drinking = new Habit();
		drinking.setName("Drinking");
		drinking.setDescription("Avoid alcohol or any other form of intoxicants");
		drinking.setFrequency("Daily");
		drinking.setLabel("Health");
		drinking.setType("BAD");
		drinking.setTarget("0 drinks");
		habitService.addHabit(drinking);

		Habit exercise = new Habit();
		exercise.setName("Exercise");
		exercise.setDescription("Running, cycling, calisthenics, cardio or any other form of physical activity");
		exercise.setFrequency("Daily");
		exercise.setLabel("Fitness");
		exercise.setType("GOOD");
		exercise.setTarget(">= 30 minutes");
		habitService.addHabit(exercise);

		Habit reading = new Habit();
		reading.setName("Reading");
		reading.setDescription("Read a book, article, blog or any other form of written content for at least 30 minutes");
		reading.setFrequency("Daily");
		reading.setLabel("Learning");
		reading.setType("GOOD");
		reading.setTarget(">= 30 minutes");
		habitService.addHabit(reading);

		Habit waterIntake = new Habit();
		waterIntake.setName("Water Intake");
		waterIntake.setDescription("Drink at least 8 glasses of water daily");
		waterIntake.setFrequency("Daily");
		waterIntake.setLabel("Health");
		waterIntake.setType("GOOD");
		waterIntake.setTarget(">= 2L / 8 glasses");
		habitService.addHabit(waterIntake);

		Habit meditation = new Habit();
		meditation.setName("Meditation");
		meditation.setDescription("Practice mindfulness, meditation or equivalent");
		meditation.setFrequency("Daily");
		meditation.setLabel("Wellness");
		meditation.setType("GOOD");
		meditation.setTarget(">= 15 minutes");
		habitService.addHabit(meditation);

		Habit journaling = new Habit();
		journaling.setName("Journaling");
		journaling.setDescription("Write down your recent thoughts, feelings, ideas, experiences, or anything that comes to mind");
		journaling.setFrequency("Daily");
		journaling.setLabel("Wellness");
		journaling.setType("GOOD");
		journaling.setTarget(">= 5 minutes / 3 ideas");
		habitService.addHabit(journaling);

		System.out.println("Habits added successfully");
	}

}

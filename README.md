# Dining_Philosophers

## Project Overview

The Dining Philosophers problem is a classic synchronization and concurrency problem that illustrates issues with resource allocation. This project provides a C implementation that solves the Dining Philosophers problem using various synchronization mechanisms.

## Table of Contents

- [Background](#background)
- [Implementation](#implementation)
- [Usage](#usage)
- [Features](#features)

## Background

The Dining Philosophers problem is a thought experiment that involves a group of philosophers sitting around a circular dining table. Each philosopher spends their life eating, sleeping and thinking. To eat, a philosopher needs two forks, one on their left and one on their right. The challenge is to design a solution to allow philosophers to eat without causing deadlocks, contention, or resource allocation conflicts.

## Implementation

The C implementation of the Dining Philosophers problem utilizes multithreading and synchronization techniques to model the philosophers and forks. The project demonstrates how to solve the problem using different approaches, such as:

- Mutex locks and condition variables
- Implementing a centralized priority queue for resource allocation

## Usage

1. Clone the repository:

   ```sh
   git clone https://github.com/yourusername/dining-philosophers.git
   make
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals(optionnal)]

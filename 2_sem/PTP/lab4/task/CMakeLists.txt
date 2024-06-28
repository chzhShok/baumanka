project(lab4)

add_executable(
        lab4
        experiment_1/main_in.c
        metrics.c
        types.h
        experiment_2/main_in.c
        experiment_3/main_in.c
        experiment_1/main_out.c
        experiment_2/main_out.c
        experiment_3/main_out.c
        experiment_1/main_ticks.c
        experiment_2/main_ticks.c
        experiment_3/main_ticks.c
)

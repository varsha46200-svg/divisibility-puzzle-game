#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SCORE 60

/*
 * Reads a single integer from standard input and discards any extra characters
 * on the same line. Returns 1 if a valid integer was read, otherwise 0.
 */
static int read_integer(int *value)
{
    int valid_input = (scanf("%d", value) == 1);
    int current_char;

    while ((current_char = getchar()) != '\n' && current_char != EOF)
    {
        /* Discard any remaining characters in the input buffer */
    }

    return valid_input;
}

/*
 * Runs one game round.
 * - Generates two divisors based on the selected difficulty level.
 * - Prompts the user to enter a positive number divisible by both divisors.
 * - Awards points only for a correct answer.
 * Returns the points earned in this round.
 */
static int play_round(int round_number, const char *level_name,
                     int max_divisor, int round_points)
{
    int divisor_one = rand() % (max_divisor - 1) + 2;   /* Range: 2 to max_divisor */
    int divisor_two = rand() % (max_divisor - 1) + 2;
    int player_answer;

    /* Ensure both divisors are different. */
    if (divisor_one == divisor_two)
    {
        divisor_two = divisor_two + 1;
        if (divisor_two > max_divisor)
        {
            divisor_two = 2;
        }
    }

    printf("\nROUND %d: %s\n", round_number, level_name);
    printf("-------------------------------------\n");
    printf("Enter a positive number divisible by both %d and %d: ",
           divisor_one, divisor_two);

    if (!read_integer(&player_answer))
    {
        printf("Invalid input. Please enter a whole number. No points awarded.\n");
        return 0;
    }

    if (player_answer <= 0)
    {
        printf("Incorrect answer. The number must be greater than 0.\n");
        return 0;
    }

    if (player_answer % divisor_one == 0 && player_answer % divisor_two == 0)
    {
        printf("Correct answer!\n");
        printf("You earned %d points.\n", round_points);
        return round_points;
    }

    printf("Incorrect answer.\n");

    if (player_answer % divisor_one == 0)
    {
        printf("%d is divisible by %d but not by %d.\n",
               player_answer, divisor_one, divisor_two);
    }
    else if (player_answer % divisor_two == 0)
    {
        printf("%d is divisible by %d but not by %d.\n",
               player_answer, divisor_two, divisor_one);
    }
    else
    {
        printf("%d is not divisible by either number.\n", player_answer);
    }

    return 0;
}

int main(void)
{
    int total_score = 0;

    /* Seed the random number generator so each game session gets different values. */
    srand((unsigned int)time(NULL));

    printf("=====================================\n");
    printf("       DIVISIBILITY PUZZLE GAME\n");
    printf("=====================================\n");

    total_score += play_round(1, "EASY", 4, 10);
    total_score += play_round(2, "MEDIUM", 6, 20);
    total_score += play_round(3, "DIFFICULT", 9, 30);

    printf("\n=====================================\n");
    printf("             FINAL RESULT\n");
    printf("=====================================\n");
    printf("Your total score is %d out of %d.\n", total_score, MAX_SCORE);

    if (total_score == MAX_SCORE)
    {
        printf("Performance: Excellent!\n");
    }
    else if (total_score >= 30)
    {
        printf("Performance: Good Job!\n");
    }
    else
    {
        printf("Performance: Keep Practising!\n");
    }

    printf("=====================================\n");

    return 0;
}

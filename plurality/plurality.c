#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int test = strcmp(candidates[i].name, name);
        if (test == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string winner;
    string next_winner;
    int most_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        //compares every value in the votes array and sets the highest value to most_votes. Winner is chosen by which candidate has the highest number of votes
        if (candidates[i].votes > candidates[i + 1].votes)
        {
            if (candidates[i].votes > most_votes)
            {
                most_votes = candidates[i].votes;
                winner = candidates[i].name;
            }
        }
        else if (candidates[i + 1].votes > candidates[i].votes)
        {
            if (candidates[i + 1].votes > most_votes)
            {
                most_votes = candidates[i + 1].votes;
                winner = candidates[i + 1].name;
            }
        }
        else if (candidates[i].votes == candidates[i + 1].votes)
        {
            if (candidates[i].votes > most_votes)
            {
                most_votes = candidates[i + 1].votes;
                winner = candidates[i].name;
            }
        }
    }
    printf("%s\n", winner);
    //checks if any other cnaiddates have an equal or higher number of votes compared to the first winner, and if they do, their name is printed
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= most_votes && (strcmp(candidates[i].name, winner) != 0))
        {
            next_winner = candidates[i].name;
            printf("%s\n", next_winner);
        }
    }
    return;
}
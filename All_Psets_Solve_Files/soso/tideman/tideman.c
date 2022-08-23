#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //loop to look over names
    for (int i = 0; i < candidate_count; i++)
    {
        //check if candidate exists
        if (strcmp(name, candidates[i]) == 0)
        {
            //update ranks
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //loop for upate each pair number
    for (int i = 0; i < candidate_count; i++)
    {
        //prefer each on that after him
        for(int j = candidate_count; j > i; j--)
        {
            //update
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //variable that store pair count
    int b  = 0;
    //loop to make each pair
    for (int i = 0; i < candidate_count; i++)
    {
        //another to see each correct pair with i
        for (int j = 0; j < candidate_count; j++)
        {
            //check if pair exists
            if (preferences[i][j] > preferences[j][i])
            {
                //updating pairs
                pairs[b].winner = i;
                pairs[b].loser = j;
                b++;
            }
        }
    }
    //updating pair count
    pair_count = b;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int y = 0; y < pair_count - i - 1; y++)
        {
            int b = preferences[pairs[y].winner][pairs[y].loser];
            int x = preferences[pairs[y + 1].winner][pairs[y + 1].loser];
            if (b < x)
            {
                pair temp = pairs[y];

                pairs[y] = pairs[y + 1];

                pairs[y + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int k;
    for (int i = 0; i < pair_count; i++)
    {
        k = 0;
        locked[pairs[i].winner][pairs[i].loser] = true;
        for (int x = 0; x < i; x++)
        {
            if (locked[pairs[i].loser][pairs[x].winner] == true)
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
                //break;
            }
        }
        /*if (k != 0)
        {
            break;
        }*/
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int n = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                n++;
                if (n == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
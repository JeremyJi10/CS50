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

int candidate_count;
int pair_count;

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

        //clear rank
        for (int k = 0; k < candidate_count; k++)
        {
            ranks[k] = -1;
        }

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (i == ranks[k])
                {
                    return false;
                }
            }
            
            ranks[rank] = i;
            
            return true;

        }
    }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //method here is iterating from first to last candidate, 
    //if candidate i was ranked at j place, then the his/her preference on every candidate ranked after him/her will increase by 1.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++) 
        {
            if (ranks[j] == i)
            {
                for (int k = j + 1; k < candidate_count; k++)
                {
                    for (int l = 0; l < candidate_count; l++)
                    {
                        if (l == ranks[k])
                        {
                            preferences[i][l] += 1;
                        }
                    }
                }
            }
        }
    }

    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //create an array containing original pairs
    pair o_pairs[candidate_count * (candidate_count - 1) / 2];

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //candidate i and j can and only can have one pair, so we just need to concern half of the combinations in preferences
            if (i < j)
            {
                //the formula shown below is used to get the index of a combination (candidate i and candidate j)
                //e.g. index of combinations of 4: [0 1]: 0; [0 2]: 1; [0 3]: 2; [1 2]: 3; [1 3]: 4; [2 3]: 5.
                if (preferences[i][j] > preferences[j][i])
                {
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].winner = i;
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].loser = j;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].winner = j;
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].loser = i;
                }
                else
                {
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].winner = -1;
                    o_pairs[((2 * candidate_count - 1 - i) * i / 2) + j - i - 1].loser = -1;
                }
            }
        }
    }

    int index = 0; //get the index of a valid pair

    for (int k = 0; k < candidate_count * (candidate_count - 1) / 2; k++)
    {
        if (o_pairs[k].winner != -1)
        {
            pairs[index].winner = o_pairs[k].winner;
            pairs[index].loser = o_pairs[k].loser;

            index += 1;
        }
    }
    pair_count = index;

    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs()
{
    pair sorted_pairs[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        sorted_pairs[i].winner = pairs[i].winner;
        sorted_pairs[i].loser = pairs[i].loser;

        // if no less than 2 elements in an array of pairs, sorting will be conducted.
        if (i >= 1)
        {
            for (int j = 0; j < i; j++)
            {
                if (preferences[sorted_pairs[i].winner][sorted_pairs[i].loser] >= preferences[sorted_pairs[j].winner][sorted_pairs[j].loser])
                {
                    int s_w = sorted_pairs[i].winner;
                    int s_l = sorted_pairs[i].loser;

                    for (int k = i; k > j; k -= 1)
                    {
                        sorted_pairs[k].winner = sorted_pairs[k - 1].winner;
                        sorted_pairs[k].loser = sorted_pairs[k - 1].loser;
                    }

                    sorted_pairs[j].winner = s_w;
                    sorted_pairs[j].loser = s_l;

                    break;
                }
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = sorted_pairs[i].winner;
        pairs[i].loser = sorted_pairs[i].loser;
    }

    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //create arraies of loser_candidate(candidates who have lost in a pair at least once ) and current_candidate(candidates who have appeared),
    //they will be used to check whether a new losing candidate will cause the cycle
    int loser_candidate[candidate_count];
    int current_candidate[candidate_count];
    
    int l_num = 0; 
    int c_num = 0;

    //clear loser_candidate and current_candidate
    for (int i = 0; i < candidate_count; i++)
    {
        loser_candidate[i] = -1;
        current_candidate[i] = -1;
    }

    for (int i = 0; i < pair_count; i++)
    {
        //update current candidate, only need to care about currently recorded candidates and the closest -1 element (j < c_num + 1)
        for (int j = 0; j < c_num + 1; j++)
        {
            if (current_candidate[j] == pairs[i].winner)
            {
                for (int k = 0; k < c_num + 1; k++)
                {
                    if (current_candidate[k] == pairs[i].loser)
                    {
                        break;
                    }
                    else if (current_candidate[k] == -1)
                    {
                        current_candidate[k] = pairs[i].loser;
                        c_num += 1;

                        break;
                    }
                }

                break;
            }
            else if (current_candidate[j] == pairs[i].loser)
            {
                for (int k = 0; k < c_num + 1; k++)
                {
                    if (current_candidate[k] == pairs[i].winner)
                    {
                        break;
                    }
                    else if (k == c_num)
                    {
                        current_candidate[k] = pairs[i].winner;
                        c_num += 1;

                        break;
                    }
                }

                break;
            }
            else if (current_candidate[j] == -1)
            {
                current_candidate[j] = pairs[i].winner;
                current_candidate[j + 1] = pairs[i].loser;
                c_num += 2;

                break;
            }
        }

        // check if new pair will cause cycle
        for (int k = 0; k < l_num + 1; k++)
        {
            if (loser_candidate[k] == pairs[i].loser)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;

                break;
            }
            else if (loser_candidate[k] == -1 && l_num != c_num - 1)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;

                loser_candidate[k] = pairs[i].loser;

                l_num += 1;

                break;
            }
        }
    }

    return;
}


// Print the winner of the election
void print_winner(void)
{
    int find_winner[candidate_count];
    
    for (int i = 0; i < candidate_count; i++)
    {
        find_winner[i] = i;
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            find_winner[pairs[i].loser] = -1;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (find_winner[i] != -1)
        {
            printf("%s\n", candidates[i]); 
        }
    }

    return;
}

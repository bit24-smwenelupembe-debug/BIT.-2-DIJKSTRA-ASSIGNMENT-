
#include <iostream>
#include <string>
using namespace std;

const int N = 20;
const int INF = 999999;

// Add a connection between two districts
void addEdge(int graph[N][N], int a, int b, int weight)
{
    graph[a][b] = weight;
    graph[b][a] = weight;
}

// Display all available districts
void displayDistricts(string district[])
{
    cout << "\n========== AVAILABLE DISTRICTS ==========\n";

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << ". " << district[i] << "\t";

        if ((i + 1) % 5 == 0)
        {
            cout << endl;
        }
    }
}

// Get and validate the user's choice
int getChoice(string message, int minimum, int maximum)
{
    int choice;

    cout << message;

    while (!(cin >> choice) ||
           choice < minimum || choice > maximum)
    {
        cout << "Invalid choice. Enter a number from "
             << minimum << " to " << maximum << ": ";

        cin.clear();
        cin.ignore(1000, '\n');
    }

    return choice;
}

// Dijkstra's shortest path algorithm
void dijkstra(int graph[N][N], string district[],
              int start, int destination)
{
    int distance[N];
    int predecessor[N];
    bool visited[N] = {false};

    // Initialize all distances and predecessors
    for (int i = 0; i < N; i++)
    {
        distance[i] = INF;
        predecessor[i] = -1;
    }

    // Distance from starting point to itself is zero
    distance[start] = 0;

    cout << "\n====================================\n";
    cout << "         DIJKSTRA ROUTE SEARCH\n";
    cout << "====================================\n";

    cout << "Starting point: " << district[start] << endl;
    cout << "Destination: " << district[destination] << endl;

    cout << "\nSearching for the shortest route...\n";

    // Continue until the destination is reached
    while (true)
    {
        int current = -1;
        int smallest = INF;

        // Find the unvisited district with the smallest distance
        for (int i = 0; i < N; i++)
        {
            if (!visited[i] && distance[i] < smallest)
            {
                smallest = distance[i];
                current = i;
            }
        }

        // Stop if no reachable district remains
        if (current == -1)
        {
            break;
        }

        // Mark the selected district as visited
        visited[current] = true;

        cout << "\nVisiting: " << district[current]
             << " (distance: " << distance[current] << ")\n";

        // Stop when the destination is reached
        if (current == destination)
        {
            cout << "Destination reached!\n";
            break;
        }

        // Check all neighbouring districts
        for (int next = 0; next < N; next++)
        {
            if (graph[current][next] > 0 && !visited[next])
            {
                int newDistance =
                    distance[current] + graph[current][next];

                cout << "  " << district[current]
                     << " -> " << district[next]
                     << ": " << distance[current]
                     << " + " << graph[current][next]
                     << " = " << newDistance;

                // Update if a shorter distance is found
                if (newDistance < distance[next])
                {
                    distance[next] = newDistance;
                    predecessor[next] = current;

                    cout << " (Updated)";
                }
                else
                {
                    cout << " (Not shorter)";
                }

                cout << endl;
            }
        }
    }

    // Display the final shortest route
    cout << "\n====================================\n";
    cout << "         SHORTEST ROUTE RESULT\n";
    cout << "====================================\n";

    // Check whether a route exists
    if (distance[destination] == INF)
    {
        cout << "No route exists between "
             << district[start] << " and "
             << district[destination] << ".\n";

        return;
    }

    // Reconstruct the route using predecessors
    int path[N];
    int length = 0;

    int current = destination;

    while (current != -1)
    {
        path[length] = current;
        length++;

        current = predecessor[current];
    }

    // Display route from start to destination
    cout << "\nShortest route:\n";

    for (int i = length - 1; i >= 0; i--)
    {
        cout << district[path[i]];

        if (i > 0)
        {
            cout << " -> ";
        }
    }

    cout << "\n\nTotal distance: "
         << distance[destination] << endl;

    cout << "\nRoute search completed!\n";
}

int main()
{
    // The 20 districts in the graph
    string district[N] =
    {
        "BA", "BT", "CK", "CR", "CT",
        "DO", "DZ", "KR", "KS", "LK",
        "LL", "MC", "MG", "MJ", "MW",
        "NE", "NS", "NU", "PH", "SA"
    };

    // Create an empty adjacency matrix
    int graph[N][N] = {0};

    // =====================================
    // CONNECTIONS AND WEIGHTS FROM THE GRAPH
    // =====================================

    addEdge(graph, 10, 9, 10);   // LL - LK
    addEdge(graph, 10, 5, 30);   // LL - DO

    addEdge(graph, 9, 7, 10);    // LK - KR
    addEdge(graph, 9, 4, 40);    // LK - CT
    addEdge(graph, 9, 16, 24);   // LK - NS

    addEdge(graph, 7, 4, 30);    // KR - CT
    addEdge(graph, 7, 2, 50);    // KR - CK

    addEdge(graph, 4, 3, 6);     // CT - CR
    addEdge(graph, 4, 0, 80);    // CT - BA

    addEdge(graph, 8, 2, 11);    // KS - CK
    addEdge(graph, 8, 13, 25);   // KS - MJ

    addEdge(graph, 2, 13, 30);   // CK - MJ
    addEdge(graph, 2, 3, 7);     // CK - CR
    addEdge(graph, 2, 0, 6);     // CK - BA

    addEdge(graph, 3, 13, 70);   // CR - MJ
    addEdge(graph, 3, 12, 40);   // CR - MG

    addEdge(graph, 13, 19, 14);  // MJ - SA
    addEdge(graph, 12, 19, 14);  // MG - SA
    addEdge(graph, 12, 11, 22);  // MG - MC

    addEdge(graph, 19, 18, 15);  // SA - PH
    addEdge(graph, 11, 18, 20);  // MC - PH
    addEdge(graph, 11, 14, 4);   // MC - MW

    addEdge(graph, 0, 6, 10);    // BA - DZ
    addEdge(graph, 6, 5, 70);    // DZ - DO
    addEdge(graph, 6, 11, 15);   // DZ - MC

    addEdge(graph, 5, 16, 11);   // DO - NS
    addEdge(graph, 5, 17, 10);   // DO - NU

    addEdge(graph, 17, 14, 40);  // NU - MW
    addEdge(graph, 17, 1, 36);   // NU - BT

    addEdge(graph, 1, 14, 21);   // BT - MW
    addEdge(graph, 14, 15, 70);  // MW - NE
    addEdge(graph, 15, 18, 10);  // NE - PH

    // =====================================
    // MAIN PROGRAM LOOP
    // =====================================

    int menuChoice;

    do
    {
        cout << "\n\n====================================\n";
        cout << "     MALAWI DISTRICT ROUTE FINDER\n";
        cout << "          DIJKSTRA ALGORITHM\n";
        cout << "====================================\n";

        // Show the available districts
        displayDistricts(district);

        // Ask the user to choose a starting point
        int start = getChoice(
            "\nChoose starting district (1-20): ", 1, 20);

        // Ask the user to choose a destination
        int destination = getChoice(
            "Choose destination district (1-20): ", 1, 20);

        // Run Dijkstra's algorithm
        dijkstra(graph, district, start - 1, destination - 1);

        // Display the menu
        cout << "\n====================================\n";
        cout << "       WHAT WOULD YOU LIKE TO DO?\n";
        cout << "====================================\n";

        cout << "1. Find another route\n";
        cout << "2. Exit program\n";

        menuChoice = getChoice("Enter your choice: ", 1, 2);

        if (menuChoice == 1)
        {
            cout << "\nStarting another route search...\n";
        }

    }
    while (menuChoice == 1);

    // Exit message
    cout << "\nThank you for using Malawi District Route Finder!\n";
    cout << "Program closed successfully.\n";

    return 0;
}

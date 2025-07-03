#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> 
#include <sstream>

int main()
{
    std::ofstream outfile("data.csv", std::ios::app); // Append mode
    if (!outfile)
    {
        perror("Error opening output file");
        return 1;
    }

    for (int fileIndex = 0; fileIndex < 150; ++fileIndex)
    {
        // Construct filename like input/in000
        std::ostringstream filename;
        filename << "../input/in" << std::setw(3) << std::setfill('0') << fileIndex;

        FILE* inputFile = freopen(filename.str().c_str(), "r", stdin);
        if (inputFile == nullptr)
        {
            perror(("Error opening file: " + filename.str()).c_str());
            continue; // Skip this file and move on
        }

        int n, m, q;
        if (scanf("%d %d %d", &n, &m, &q) != 3)
        {
            fprintf(stderr, "Failed to read n, m, q from %s\n", filename.str().c_str());
            continue;
        }

        for (int i = 0; i < m; ++i)
        {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
        }

        std::vector<int> times;
        for (int i = n + m; i < n + m + q; ++i)
        {
            int op;
            scanf("%d", &op);
            if (op == 0)
            {
                int t;
                scanf("%d", &t);
                times.push_back(t);
            }
            else
            {
                int x, y, w, t;
                scanf("%d %d %d %d", &x, &y, &w, &t);
                times.push_back(t);
            }
        }

        // Write result to CSV
        outfile << n << "," << m << "," << q << "," << 50011 << "," ;
        for (size_t i = 0; i < times.size(); ++i)
        {
            outfile << times[i];
            if (i != times.size() - 1)
                outfile << ";";
        }
        outfile << "\n";
    }

    outfile.close();
    return 0;
}


#include <vector>
using std::vector;

class PawnPosition{
    private:
        vector<vector<unsigned int>> position;
    public:
        PawnPosition() = delete;
        PawnPosition(const PawnPosition&) = delete;
        PawnPosition(vector<vector<unsigned int>> position);
        ~PawnPosition() = default;
        void ChangePosition(vector<vector<unsigned int>> new_position);
};
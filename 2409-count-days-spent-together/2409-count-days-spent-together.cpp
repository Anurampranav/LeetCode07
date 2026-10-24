class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        string start = max(arriveAlice, arriveBob);
        string end = min(leaveAlice, leaveBob);

        if (start > end) {
            return 0;
        }

        int startDay = 0, endDay = 0;

        for (int i = 0; i < stoi(start.substr(0, 2)) - 1; i++) {
            startDay += days[i];
        }
        startDay += stoi(start.substr(3, 2));

        for (int i = 0; i < stoi(end.substr(0, 2)) - 1; i++) {
            endDay += days[i];
        }
        endDay += stoi(end.substr(3, 2));

        return endDay - startDay + 1;
    }
};
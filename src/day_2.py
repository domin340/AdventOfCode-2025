def part_1():
    with open("inputs/day_2.txt") as f:
        content = f.read()

        _sum = 0;
        for range_pair in content.split(','):
            range_split = range_pair.split('-')
            (left, right) = tuple([int(i) for i in range_split])
            for i in range(int(left), int(right) + 1):
                str_i = str(i)
                if len(str_i) % 2 == 1:
                    continue;

                midpoint = len(str_i) // 2
                if (str_i[:midpoint] == str_i[midpoint:]):
                    _sum += i
        
        print(_sum)

if __name__ == "__main__":
    part_1()


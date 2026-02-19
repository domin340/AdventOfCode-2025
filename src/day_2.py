def get_range_pairs(s: str) -> list[tuple[int, int]]:
    pairs = []

    for range_pair in s.split(','):
        range_split = range_pair.split('-')
        (left, right) = tuple([int(i) for i in range_split])
        pairs.append((left, right))

    return pairs


def part_1():
    _sum = 0;
    content: str

    with open('inputs/day_2.txt', 'r') as f:
        content = f.read()

    for (left, right) in get_range_pairs(content):
        for i in range(left, right + 1):
            str_i = str(i)
            if len(str_i) % 2 == 1:
                continue;

            midpoint = len(str_i) // 2
            if (str_i[:midpoint] == str_i[midpoint:]):
                _sum += i
        
    print(_sum)


class Window:
    def __init__(self, item, n: int, start: int = 0):
        if n > len(item):
            raise Exception("n is larger than the lenght of the array")

        self.to_observe = item
        self.n = n
        self.cur_n = start

    def __iter__(self):
        return self

    def __next__(self):
        if (self.cur_n >= len(self.to_observe)):
            raise StopIteration

        start = self.cur_n
        end = self.cur_n + self.n
        
        self.cur_n += self.n

        return self.to_observe[start:end]

    @property
    def copy(self):
        return Window(self.to_observe, self.n, self.cur_n)

    def against(self, expected_view):
        for w in self.copy:
            yield (w == expected_view)


def part_2():
    # shit is slow asf but I didn't have much time to think about it today
    # method works by individually checking every single possible substring like a window
    # [ (1) 2  1 2 ] -> False
    # [ (1  2) 1 2 ] -> True! because another window is also 12
    def _repeats(n: int) -> bool:
        _s = str(n)
        _len = len(_s)
        
        midpoint = _len // 2
        if _len % 2 == 0 and _s[midpoint:] == _s[:midpoint]:
            return True

        for j in range(1, (_len // 2) + 1):
            if _len % j != 0:
                continue

            _sub = _s[:j]
            s_window = Window(_s, len(_sub), j)
            if all(s_window.against(_sub)):
                return True
        
        return False


    _sum = 0;
    content: str

    with open('inputs/day_2.txt', 'r') as f:
        content = f.read()

    for (left, right) in get_range_pairs(content):
        for i in range(left, right+1):
            if _repeats(i):
                _sum += i

    print(_sum)


if __name__ == '__main__':
    part_2()


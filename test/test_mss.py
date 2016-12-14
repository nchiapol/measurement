import unittest
import mss

class MSStester(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.a = mss.MSS(2, 0.3, 0.1)
        self.b = mss.MSS(3, 0.4, 0.1)

    def test_additions_uncorrelated(self):
        #given
        expect_val = 5
        expect_stat = 0.5
        expect_syst = 0.141
        #when
        c = self.a+self.b
        d = mss.add(self.a, self.b)
        self.a += self.b
        #then
        for v in [c, d, self.a]:
            self.assertEqual(v.val, expect_val)
            self.assertEqual(v.stat, expect_stat)
            self.assertAlmostEqual(v.syst, expect_syst, 3)

    def test_addition_correlated(self):
        #given
        expect_val = 5
        expect_stat = 0.7
        expect_syst = 0.2
        #when
        v = mss.add(self.a, self.b, 1, 1)
        #then
        self.assertEqual(v.val, expect_val)
        self.assertEqual(v.stat, expect_stat)
        self.assertAlmostEqual(v.syst, expect_syst, 3)


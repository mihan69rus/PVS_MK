class ComplexNumber
{
	double Re;
	double Im;
public:
	constexpr ComplexNumber(double x, double y):
		Re(x),
		Im(y)
	{}
	constexpr ComplexNumber():
		Re(0),
		Im(0)
	{}
	constexpr void SetRe(double x) { Re = x; }
	constexpr void SetIm(double y) { Im = y; }
	constexpr double GetRe() const { return Re; }
	constexpr double GetIm() const { return Im; }
	constexpr bool operator==(ComplexNumber const& a) const { return (this->GetRe() == a.GetRe()) && (this->GetIm() == a.GetIm()); }
};

/* check code */

constexpr ComplexNumber Conjugate(const ComplexNumber& x) {
	ComplexNumber res;
	res.SetRe(x.GetRe());
	res.SetIm(-x.GetIm());
	return res;
}

int main() {
	constexpr ComplexNumber	a(1, 2);
	constexpr ComplexNumber b(1, -2);
	constexpr auto c = Conjugate(a);
	static_assert(b == c, "failed");
}
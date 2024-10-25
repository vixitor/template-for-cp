struct Fraction{
    long long n,d;
    Fraction(long long x,long long y) : n(x),d(y){
        simplify();
    }
    Fraction(long long x) : n(x),d(1){
        simplify();
    }
    Fraction simplify(){
        long long t = std::gcd(n,d);
        n /= t;
        d /= t;
    }
    Fraction operator + (const Fraction& that) {
        return Fraction(n * that.d + that.n * d,d * that.d);
    }
    Fraction operator -(const Fraction & that){
        return Fraction(n * that.d - that.n * d,d * that.d);
    }
    Fraction operator * (const Fraction& that){
        return Fraction(n * that.n,d * that.d);
    }
    Fraction operator / (const Fraction& that){
        return Fraction(n * that.d,d * that.n);
    }
};
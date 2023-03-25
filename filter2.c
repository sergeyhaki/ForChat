
void inverse_fft(vector<complex<double>>& a) {

    int n = a.size();
    if (n == 1) {
        return;
    }

    vector<complex<double>> a0(n/2), a1(n/2);
    for (int i = 0; i < n/2; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }

    inverse_fft(a0);
    inverse_fft(a1);

    double angle = 2*M_PI/n;
    complex<double> w(1), wn(cos(angle), sin(angle));

    for (int i = 0; i < n/2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        w *= wn;
    }
}
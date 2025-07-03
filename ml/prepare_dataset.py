#!/usr/bin/env python3
import numpy as np, pandas as pd, argparse, pathlib, joblib

NUM_BINS = 64

def build_features(df):
    feats, hists = [], []
    for _, row in df.iterrows():
        n, m, T, q = row[['n','m','T','q']]
        times = list(map(int, str(row['update_times']).split(';')))
        feats.append([
            np.log1p(n), np.log1p(m), np.log1p(T),
            np.log1p(q),
            (2*m)/(n*(n-1)+1e-9)
        ])
        hist, _ = np.histogram(times, bins=NUM_BINS, range=(0, T))
        hist = hist.astype(np.float32)
        hist /= (hist.sum() + 1e-9)
        hists.append(hist)
    return np.asarray(feats, np.float32), np.asarray(hists, np.float32)

def main(csv, out):
    df = pd.read_csv(csv)
    X, Y = build_features(df)
    joblib.dump({'X': X, 'Y': Y}, out)
    print(f"Saved dataset to {out}  | X:{X.shape} Y:{Y.shape}")

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('csv'), ap.add_argument('-o','--out',default='dataset.pkl')
    main(**vars(ap.parse_args()))

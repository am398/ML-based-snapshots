#!/usr/bin/env python3
import joblib, argparse
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline

NUM_BINS = 64

def main(dataset_pkl, model_out):
    data = joblib.load(dataset_pkl)
    X, Y = data['X'], data['Y']
    pipe = make_pipeline(
        StandardScaler(),
        MLPRegressor(hidden_layer_sizes=(128,128),
                     activation='relu',
                     solver='adam',
                     max_iter=400,
                     random_state=42)
    )
    pipe.fit(X, Y)
    joblib.dump(pipe, model_out)
    print("Model saved to", model_out)

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('dataset_pkl'), ap.add_argument('-o','--model_out',default='hist_model.pkl')
    main(**vars(ap.parse_args()))

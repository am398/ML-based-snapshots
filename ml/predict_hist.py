# pybind-friendly: importable & callable
import numpy as np, joblib, pathlib, os

_NUM_BINS = 64
_model = None

def _lazy_load():
    global _model
    if _model is None:
        model_path = pathlib.Path(__file__).parent / "hist_model.pkl"
        if not model_path.exists():
            raise FileNotFoundError("hist_model.pkl not found; train first.")
        _model = joblib.load(model_path)

def predict_hist(n:int, m:int, T:int, q:int):
    """
    Returns list[float] length 64 a normalized density histogram.
    """
    _lazy_load()
    v = np.array([[
        np.log1p(n), np.log1p(m), np.log1p(T),
        np.log1p(q),
        (2*m)/(n*(n-1)+1e-9)
    ]], dtype=np.float32)
    hist = _model.predict(v)[0]
    hist = np.clip(hist, 0, None)
    hist /= (hist.sum() + 1e-9)
    print(f"[Python] predict_hist called with n={n}, m={m}, T={T}, q={q}")
    return hist.tolist()
